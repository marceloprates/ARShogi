#include "Piece.h"
#define QUAT

Piece::Piece(char* model_name, char* patt_name)
{
	this->Init(model_name,patt_name);
}

Piece::~Piece(void)
{
}

void Piece::Draw()
{
	glPushMatrix(); // Save world coordinate system.

		glTranslatef(0.0, 0.0, 0.0); // Place base of cube on marker surface.
#ifndef QUAT
		glRotatef((float)(this->rotate[1] * RAD_TO_PI), this->up[0], this->up[1], this->up[2]);
		glRotatef((float)(this->rotate[0] * RAD_TO_PI), this->right[0] , this->right[1] , this->right[2]);
		glRotatef((float)(this->rotate[2] * RAD_TO_PI), this->front[0] , this->front[1] , this->front[2]);
#else
		glRotatef(glm::angle(orientation), orientation.x, orientation.y, orientation.z);
#endif
		//glRotatef(90.0, 1.0, 0.0, 0.0);

		glScalef(this->scale[0], this->scale[1], this->scale[2]);
		
		glTranslatef(this->translate[0], this->translate[1], this->translate[2]);

		glDisable(GL_LIGHTING);	// Just use colours.

		glmDraw(this->model, GLM_TEXTURE | GLM_MATERIAL);

	glPopMatrix();	// Restore world coordinate system.
}

void Piece::Reset()
{
	this->right[0] = 1.0; this->right[1] = 0.0, this->right[2] = 0.0;
	this->up[0] = 0.0; this->up[1] = 1.0; this->up[2] = 0.0;
	this->front[0] = 0.0; this->front[1] = 0.0; this->front[2] = 1.0;

	this->rotate[0] = 0.0; this->rotate[1] = 0.0; this->rotate[2] = 0.0;
	this->scale[0] = 1.0; this->scale[1] = 1.0; this->scale[2] = 1.0;
	this->translate[0] = 0.0; this->translate[1] = 0.0; this->translate[2] = 0.0;
}

void Piece::RotateX(double angle)
{
	//angle = angle*0.0174533;
#ifndef QUAT
	Rotate(this->right,this->right,angle);
	Rotate(this->right,this->up,angle);
	Rotate(this->right,this->front,angle);
#else
	ChangeOrientation(angle, glm::vec3(1.0, 0.0, 0.0));
#endif

	this->rotate[0] += angle;
}

void Piece::RotateY(double angle)
{
	//angle = angle*0.0174533;
#ifndef QUAT
	Rotate(this->up,this->up,angle);
	Rotate(this->up,this->right,angle);
	Rotate(this->up,this->front,angle);
#else
	ChangeOrientation(angle, glm::vec3(0.0, 1.0, 0.0));
#endif
	this->rotate[1] += angle;
}

void Piece::RotateZ(double angle)
{
	//angle = angle*0.0174533;
#ifndef QUAT
	Rotate(this->front,this->front,angle);
	Rotate(this->front,this->right,angle);
	Rotate(this->front,this->up,angle);
#else
	ChangeOrientation(angle, glm::vec3(0.0, 0.0, 1.0));
#endif
	this->rotate[2] += angle;
}

void Piece::Scale(double sx, double sy, double sz)
{
	this->scale[0] *= sx;
	this->scale[1] *= sy;
	this->scale[2] *= sz;
}

void Piece::Scale(double factor)
{
	this->Scale(factor,factor,factor);
}

void Piece::ScaleX(double s)
{
	this->Scale(s,this->scale[1],this->scale[2]);
}

void Piece::ScaleY(double s)
{
	this->Scale(this->scale[0], s, this->scale[2]);
}

void Piece::ScaleZ(double s)
{
	this->Scale(this->scale[0], this->scale[1], s);
}

void Piece::SetSize(double sx, double sy, double sz)
{
	this->scale[0] = sx;
	this->scale[1] = sy;
	this->scale[2] = sz;
}

void Piece::SetSize(double s)
{
	this->SetSize(s,s,s);
}

void Piece::SetSizeX(double s)
{
	this->SetSize(s,this->scale[1],this->scale[2]);
}

void Piece::SetSizeY(double s)
{
	this->SetSize(this->scale[0],s,this->scale[2]);
}

void Piece::SetSizeZ(double s)
{
	this->SetSize(this->scale[0],this->scale[1],s);
}

void Piece::Translate(double tx, double ty, double tz)
{
	this->translate[0] += tx;
	this->translate[1] += ty;
	this->translate[2] += tz;
}

void Piece::TranslateX(double t)
{
	this->Translate(t, 0.0, 0.0);
}

void Piece::TranslateY(double t)
{
	this->Translate(0.0, t, 0.0);
}

void Piece::TranslateZ(double t)
{
	this->Translate(0.0, 0.0, t);
}

void Piece::SetPosition(double x, double y, double z)
{
	this->translate[0] = x;
	this->translate[1] = y;
	this->translate[2] = z;
}

void Piece::SetPositionX(double x)
{
	this->SetPosition(x,this->translate[1],this->translate[2]);
}

void Piece::SetPositionY(double y)
{
	this->SetPosition(this->translate[0],y,this->translate[2]);
}

void Piece::SetPositionZ(double z)
{
	this->SetPosition(this->translate[0],this->translate[1],z);
}

void Piece::Animate()
{
}

void Piece::Init(char* model_name, char* patt_name)
{
	// init angle

	this->angle = 0.0;

	// init vectors

	this->right[0] = 1.0; this->right[1] = 0.0, this->right[2] = 0.0;
	this->up[0] = 0.0; this->up[1] = 1.0; this->up[2] = 0.0;
	this->front[0] = 0.0; this->front[1] = 0.0; this->front[2] = 1.0;

	this->orientation = glm::fquat();

	this->rotate[0] = 0.0; this->rotate[1] = 0.0; this->rotate[2] = 0.0;
	this->scale[0] = 1.0; this->scale[1] = 1.0; this->scale[2] = 1.0;
	this->translate[0] = 0.0; this->translate[1] = 0.0; this->translate[2] = 0.0;

	// init model

	char model_path[50];

	sprintf(model_path,"../Models/%s/%s.obj",model_name,model_name);

	this->model = glmReadOBJ(model_path);

	// init pattern

	char patt_path[50];

	sprintf(patt_path,"Data/custom/%s.patt",patt_name);

	this->patt_path = patt_path;

	setupMarker(this->patt_path, &(this->patt_id));

	this->patt_width = 80.0;
	this->patt_centre[0] = 0.0; this->patt_centre[1] = 0.0;
	this->patt_found = FALSE;
}

int Piece::setupMarker(const char *patt_name, int *patt_id)
{
	
    if((*patt_id = arLoadPatt(patt_name)) < 0) 
	{
        fprintf(stderr, "setupMarker(): pattern load error !!\n");
        return (FALSE);
    }
	
	return (TRUE);
}

void Piece::Rotate(double axis[3], double vector[3], double angle)
{
	double ux = axis[0];
	double uy = axis[1];
	double uz = axis[2];

	double x = vector[0];
	double y = vector[1];
	double z = vector[2];

	vector[0] = x*(cosf(angle) + ux*ux*(1-cosf(angle))) + y*(ux*uy*(1-cosf(angle))-uz*sinf(angle)) + z*(ux*uz*(1-cosf(angle)) + uy*sinf(angle));
	vector[1] = x*(uy*ux*(1-cosf(angle)) + uz*sinf(angle)) + y*(cosf(angle) + uy*uy*(1-cosf(angle))) + z*(uy*uz*(1-cosf(angle)) - ux*sinf(angle));
	vector[2] = x*(uz*ux*(1-cosf(angle)) - uy*sinf(angle)) + y*(uz*uy*(1-cosf(angle)) + ux*sinf(angle)) + z*(cosf(angle) + uz*uz*(1-cosf(angle)));
}

void Piece::ChangeOrientation(double angle, glm::vec3 axis)
{
	glm::vec3 normalizedAxis = glm::normalize(axis);
    
    axis = axis * sinf(angle / 2.0f);
    double scalar = cosf(angle / 2.0f);
    
    glm::fquat offset(scalar, axis.x, axis.y, axis.z);

	this->orientation = glm::normalize(this->orientation * offset);
}