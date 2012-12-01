

// ============================================================================
//	Includes
// ============================================================================

#include <stdio.h>
#include <stdlib.h>					// malloc(), free()
#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif
#include <AR/config.h>
#include <AR/video.h>
#include <AR/param.h>			// arParamDisp()
#include <AR/ar.h>
#include <AR/gsub_lite.h>
#include <list>

#include "glm.h"
#include "Piece.h"

// ============================================================================
//	Constants
// ============================================================================

#define VIEW_SCALEFACTOR		0.025		// 1.0 ARToolKit unit becomes 0.025 of my OpenGL units.
#define VIEW_DISTANCE_MIN		0.1			// Objects closer to the camera than this will not be displayed.
#define VIEW_DISTANCE_MAX		100.0		// Objects further away from the camera than this will not be displayed.

// ============================================================================
//	Global variables
// ============================================================================

// Preferences.
static int prefWindowed = TRUE;
static int prefWidth = 640;					// Fullscreen mode width.
static int prefHeight = 480;				// Fullscreen mode height.
static int prefDepth = 32;					// Fullscreen mode bit depth.
static int prefRefresh = 0;					// Fullscreen mode refresh rate. Set to 0 to use default rate.

// Image acquisition.
static ARUint8		*gARTImage = NULL;

// Marker detection.
static int			gARTThreshhold = 100;
static long			gCallCountMarkerDetect = 0;

// Transformation matrix retrieval.
static double		gPatt_width     = 80.0;	// Per-marker, but we are using only 1 marker.
static double		gPatt_centre[2] = {0.0, 0.0}; // Per-marker, but we are using only 1 marker.
static double		gPatt_trans[3][4];		// Per-marker, but we are using only 1 marker.
static int			gPatt_found = FALSE;	// Per-marker, but we are using only 1 marker.
static int			gPatt_id;				// Per-marker, but we are using only 1 marker.

// Drawing.
static ARParam		gARTCparam;
static ARGL_CONTEXT_SETTINGS_REF gArglSettings = NULL;
static int gDrawRotate = FALSE;
static float gDrawRotateAngle = 0;			// For use in drawing.

// ============================================================================
// Pieces
// ============================================================================
double angle = 0.0;

static Piece* gabumon; 
static Piece* mewtwo;

static Piece* king;
static Piece* rook;
static Piece* bishop;
static Piece* gold_general;
static Piece* silver_general;
static Piece* knight;
static Piece* lance;
static Piece* pawn;

static std::list<Piece*> pieces;

// ============================================================================
//	Functions
// ============================================================================

static void Init(void)
{
	GLMmodel* m;

	m = glmReadOBJ("../Models/gabumon.obj"); glmScale(m,1.0);
	gabumon = new Piece(glmReadOBJ("../Models/gabumon.obj"),"Data/custom/patt1.patt");

	m = glmReadOBJ("../Models/mewtwo/mewtwo.obj"); glmScale(m,0.1);
	mewtwo = new Piece(m,"Data/custom/patt2.patt");

	/*
	king = new Piece(glmReadOBJ("../Models/king.obj"));
	rook = new Piece(glmReadOBJ("../Models/rook.obj"));
	bishop = new Piece(glmReadOBJ("../Models/bishop.obj"));
	gold_general = new Piece(glmReadOBJ("../Models/gold_general.obj"));
	silver_general = new Piece(glmReadOBJ("../Models/silver_general.obj"));
	knight = new Piece(glmReadOBJ("../Models/knight.obj"));
	lance = new Piece(glmReadOBJ("../Models/lance.obj"));
	pawn = new Piece(glmReadOBJ("../Models/pawn.obj"));
	*/

	pieces.push_back(gabumon);
	pieces.push_back(mewtwo);
	/*
	pieces.push_back(king);
	pieces.push_back(rook);
	pieces.push_back(bishop);
	pieces.push_back(gold_general);
	pieces.push_back(silver_general);
	pieces.push_back(knight);
	pieces.push_back(lance);
	pieces.push_back(pawn);
	*/
}

static void DrawSomething(void)
{
	gabumon->Draw();
}

static int setupCamera(const char *cparam_name, char *vconf, ARParam *cparam)
{	
    ARParam			wparam;
	int				xsize, ysize;
	
    // Open the video path.
    if (arVideoOpen(vconf) < 0) 
	{
    	fprintf(stderr, "setupCamera(): Unable to open connection to camera.\n");
    	return (FALSE);
	}
	
    // Find the size of the window.
    if (arVideoInqSize(&xsize, &ysize) < 0)
	{
		return (FALSE);
	}
    
	fprintf(stdout, "Camera image size (x,y) = (%d,%d)\n", xsize, ysize);
	
	// Load the camera parameters, resize for the window and init.
    if (arParamLoad(cparam_name, 1, &wparam) < 0)
	{
		fprintf(stderr, "setupCamera(): Error loading parameter file %s for camera.\n", cparam_name);
        return (FALSE);
    }

    arParamChangeSize(&wparam, xsize, ysize, cparam);
    fprintf(stdout, "*** Camera Parameter ***\n");
    arParamDisp(cparam);
	
    arInitCparam(cparam);

	if (arVideoCapStart() != 0)
	{
    	fprintf(stderr, "setupCamera(): Unable to begin camera data capture.\n");
		return (FALSE);		
	}
	
	return (TRUE);
}

static int setupMarker(const char *patt_name, int *patt_id)
{
	
    if((*patt_id = arLoadPatt(patt_name)) < 0) 
	{
        fprintf(stderr, "setupMarker(): pattern load error !!\n");
        return (FALSE);
    }
	
	return (TRUE);
}

// Report state of ARToolKit global variables arFittingMode,
// arImageProcMode, arglDrawMode, arTemplateMatchingMode, arMatchingPCAMode.
static void debugReportMode(void)
{
	if(arFittingMode == AR_FITTING_TO_INPUT )
	{
		fprintf(stderr, "FittingMode (Z): INPUT IMAGE\n");
	} 
	else
	{
		fprintf(stderr, "FittingMode (Z): COMPENSATED IMAGE\n");
	}
	
	if( arImageProcMode == AR_IMAGE_PROC_IN_FULL )
	{
		fprintf(stderr, "ProcMode (X)   : FULL IMAGE\n");
	} 
	else
	{
		fprintf(stderr, "ProcMode (X)   : HALF IMAGE\n");
	}
	
	if (arglDrawModeGet(gArglSettings) == AR_DRAW_BY_GL_DRAW_PIXELS)
	{
		fprintf(stderr, "DrawMode (C)   : GL_DRAW_PIXELS\n");
	} 
	else if (arglTexmapModeGet(gArglSettings) == AR_DRAW_TEXTURE_FULL_IMAGE) 
	{
		fprintf(stderr, "DrawMode (C)   : TEXTURE MAPPING (FULL RESOLUTION)\n");
	} 
	else 
	{
		fprintf(stderr, "DrawMode (C)   : TEXTURE MAPPING (HALF RESOLUTION)\n");
	}
		
	if( arTemplateMatchingMode == AR_TEMPLATE_MATCHING_COLOR ) 
	{
		fprintf(stderr, "TemplateMatchingMode (M)   : Color Template\n");
	} 
	else 
	{
		fprintf(stderr, "TemplateMatchingMode (M)   : BW Template\n");
	}
	
	if( arMatchingPCAMode == AR_MATCHING_WITHOUT_PCA ) 
	{
		fprintf(stderr, "MatchingPCAMode (P)   : Without PCA\n");
	} 
	else 
	{
		fprintf(stderr, "MatchingPCAMode (P)   : With PCA\n");
	}
}

static void Quit(void)
{
	arglCleanup(gArglSettings);
	arVideoCapStop();
	arVideoClose();
	exit(0);
}

static void Keyboard(unsigned char key, int x, int y)
{
	int mode;
	switch (key) {
		case 0x1B:						// Quit.
		case 'Q':
		case 'q':
			Quit();
			break;
		case ' ':
			gDrawRotate = !gDrawRotate;
			break;
		case 'C':
		case 'c':
			mode = arglDrawModeGet(gArglSettings);
			if (mode == AR_DRAW_BY_GL_DRAW_PIXELS) {
				arglDrawModeSet(gArglSettings, AR_DRAW_BY_TEXTURE_MAPPING);
				arglTexmapModeSet(gArglSettings, AR_DRAW_TEXTURE_FULL_IMAGE);
			} else {
				mode = arglTexmapModeGet(gArglSettings);
				if (mode == AR_DRAW_TEXTURE_FULL_IMAGE)	arglTexmapModeSet(gArglSettings, AR_DRAW_TEXTURE_HALF_IMAGE);
				else arglDrawModeSet(gArglSettings, AR_DRAW_BY_GL_DRAW_PIXELS);
			}
			fprintf(stderr, "*** Camera - %f (frame/sec)\n", (double)gCallCountMarkerDetect/arUtilTimer());
			gCallCountMarkerDetect = 0;
			arUtilTimerReset();
			debugReportMode();
			break;
		case 'D':
		case 'd':
			arDebug = !arDebug;
			break;
		case '?':
		case '/':
			printf("Keys:\n");
			printf(" q or [esc]    Quit demo.\n");
			printf(" c             Change arglDrawMode and arglTexmapMode.\n");
			printf(" d             Activate / deactivate debug mode.\n");
			printf(" ? or /        Show this help.\n");
			printf("\nAdditionally, the ARVideo library supplied the following help text:\n");
			arVideoDispOption();
			break;
		default:
			break;
	}
}

static void AnimateModels(void)
{
	for(std::list<Piece*>::iterator it = pieces.begin(); it != pieces.end(); it++)
	{
		(*it)->Animate();
	}
}

static void Idle(void)
{
	static int ms_prev;
	int ms;
	float s_elapsed;
	ARUint8 *image;

	ARMarkerInfo    *marker_info;					// Pointer to array holding the details of detected markers.
    int             marker_num;						// Count of number of markers detected.
    int             j, k;

	// Find out how long since Idle() last ran.
	ms = glutGet(GLUT_ELAPSED_TIME);
	s_elapsed = (float)(ms - ms_prev) * 0.001;
	if (s_elapsed < 0.01f) return; // Don't update more often than 100 Hz.
	ms_prev = ms;

	// Grab a video frame.
	if ((image = arVideoGetImage()) != NULL) 
	{
		gARTImage = image;	// Save the fetched image.
		
		gCallCountMarkerDetect++; // Increment ARToolKit FPS counter.
		
		// Detect the markers in the video frame.
		if (arDetectMarker(gARTImage, gARTThreshhold, &marker_info, &marker_num) < 0) 
		{
			exit(-1);
		}

		for(std::list<Piece*>::iterator it = pieces.begin(); it != pieces.end(); it++)
		{
			(*it)->patt_found = FALSE;	// Invalidate any previous detected markers.

			// Check through the marker_info array for highest confidence
			// visible marker matching our preferred pattern.

			k = -1;
			for (j = 0; j < marker_num; j++) 
			{				
				if (marker_info[j].id == (*it)->patt_id)
				{

					if (k == -1) // First marker detected.
					{
						k = j;
					}
					else if(marker_info[j].cf > marker_info[k].cf) // Higher confidence marker detected.
					{
						k = j;
					}
				}
			}

			if (k != -1) 
			{
				// Get the transformation between the marker and the real camera into gPatt_trans.
				arGetTransMat(&(marker_info[k]), (*it)->patt_centre, (*it)->patt_width, (*it)->patt_trans);
				(*it)->patt_found = TRUE;
			}

		}

		AnimateModels();

		// Tell GLUT the display has changed.
		glutPostRedisplay();
	}
}

//
//	This function is called on events when the visibility of the
//	GLUT window changes (including when it first becomes visible).
//
static void Visibility(int visible)
{
	if (visible == GLUT_VISIBLE) 
	{
		glutIdleFunc(Idle);
	} 
	else 
	{
		glutIdleFunc(NULL);
	}
}

//
//	This function is called when the
//	GLUT window is resized.
//
static void Reshape(int w, int h)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Call through to anyone else who needs to know about window sizing here.
}

//
// This function is called when the window needs redrawing.
//
static void Display(void)
{
    GLdouble p[16];
	GLdouble m[16];

	// Select correct buffer for this context.
	glDrawBuffer(GL_BACK);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the buffers for new frame.

	arglDispImage(gARTImage, &gARTCparam, 1.0, gArglSettings);	// zoom = 1.0.
	arVideoCapNext();
	gARTImage = NULL; // Image data is no longer valid after calling arVideoCapNext().

	for(std::list<Piece*>::iterator it = pieces.begin(); it != pieces.end(); it++)
	{
		if ((*it)->patt_found) // gPatt_found
		{
			// Projection transformation.
			arglCameraFrustumRH(&gARTCparam, VIEW_DISTANCE_MIN, VIEW_DISTANCE_MAX, p);
			glMatrixMode(GL_PROJECTION);
			glLoadMatrixd(p);
			glMatrixMode(GL_MODELVIEW);

			// Viewing transformation.
			glLoadIdentity();
			// Lighting and geometry that moves with the camera should go here.
			// (I.e. must be specified before viewing transformations.)
			//none

			// ARToolKit supplied distance in millimetres, but I want OpenGL to work in my units.
			arglCameraViewRH((*it)->patt_trans, m, VIEW_SCALEFACTOR);
			glLoadMatrixd(m);

			// All other lighting and geometry goes here.

			(*it)->Draw();

		} 
		
		// Any 2D overlays go here.
		//none
	}

	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	char glutGamemode[32];
	const char *cparam_name = "Data/camera_para.dat";
	//
	// Camera configuration.
	//
#ifdef _WIN32
	char			*vconf = "Data\\WDM_camera_flipV.xml";
#else
	char			*vconf = "";
#endif
	const char *patt_name  = "Data/custom/patt1.patt";
	
	// ----------------------------------------------------------------------------
	// Library inits.
	//

	glutInit(&argc, argv);

	// ----------------------------------------------------------------------------
	// Hardware setup.
	//

	if (!setupCamera(cparam_name, vconf, &gARTCparam)) 
	{
		fprintf(stderr, "main(): Unable to set up AR camera.\n");
		exit(-1);
	}

	/*
	if (!setupMarker(patt_name, &gPatt_id)) 
	{
		fprintf(stderr, "main(): Unable to set up AR marker.\n");
		exit(-1);
	}
	*/

	// ----------------------------------------------------------------------------
	// Library setup.
	//

	// Set up GL context(s) for OpenGL to draw into.
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	
	if (!prefWindowed) 
	{
		if (prefRefresh)
		{
			sprintf(glutGamemode, "%ix%i:%i@%i", prefWidth, prefHeight, prefDepth, prefRefresh);
		}
		else
		{
			sprintf(glutGamemode, "%ix%i:%i", prefWidth, prefHeight, prefDepth);
		}
		
		glutGameModeString(glutGamemode);

		glutEnterGameMode();
	} 
	else 
	{
		glutInitWindowSize(prefWidth, prefHeight);

		glutCreateWindow(argv[0]);
	}

	// Setup argl library for current context.
	if ((gArglSettings = arglSetupForCurrentContext()) == NULL) 
	{
		fprintf(stderr, "main(): arglSetupForCurrentContext() returned error.\n");

		exit(-1);
	}

	debugReportMode();

	glEnable(GL_DEPTH_TEST);

	arUtilTimerReset();

	// ----------------------------------------------------------------------------
	// Program Init
	//

	Init();

	// Register GLUT event-handling callbacks.
	// NB: Idle() is registered by Visibility.

	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutVisibilityFunc(Visibility);
	glutKeyboardFunc(Keyboard);
	
	glutMainLoop();
	
	return (0);
}