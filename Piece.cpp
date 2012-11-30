#include "Piece.h"


Piece::Piece(GLMmodel* model)
{
	this->model = model;

	this->right[0] = 1.0; this->right[1] = 0.0, this->right[2] = 0.0;
	this->up[0] = 0.0; this->up[1] = 1.0; this->up[2] = 0.0;
	this->front[0] = 0.0; this->front[1] = 0.0; this->front[2] = 1.0;

	this->rotate[0] = 0.0; this->rotate[1] = 0.0; this->rotate[2] = 0.0;
	this->scale[0] = 1.0; this->scale[1] = 1.0; this->scale[2] = 1.0;
	this->translate[0] = 0.0; this->translate[1] = 0.0; this->translate[2] = 0.0;

	this->patt_name = "Data/custom/patt1.patt";

	setupMarker(this->patt_name, &(this->patt_id));

	this->patt_width = 80.0;
	this->patt_centre[0] = 0.0; this->patt_centre[1] = 0.0;
	this->patt_found = FALSE;
}

Piece::Piece(char* address)
{
	Piece(glmReadOBJ(address));
}

Piece::Piece(PieceType pieceType)
{
	switch(pieceType)
	{
		case King:
			Piece("../Models/king.obj");
			break;
		case Rook:
			Piece("../Models/rook.obj");
			break;
		case Bishop:
			Piece("../Models/bishop.obj");
			break;
		case Gold_general:
			Piece("../Models/gold_general.obj");
			break;
		case Silver_general:
			Piece("../Models/silver_general.obj");
			break;
		case Knight:
			Piece("../Models/knight.obj");
			break;
		case Lance:
			Piece("../Models/lance.obj");
			break;
		case Gabumon:
			Piece("../Models/gabumon.obj");
			break;
	}
}

void Piece::Draw()
{
	glPushMatrix(); // Save world coordinate system.

		glTranslatef(this->translate[0], this->translate[1], this->translate[2]); // Place base of cube on marker surface.

		glRotatef(90.0, 1.0, 0.0, 0.0); // Rotate about z axis.

		glRotatef((float)(this->rotate[1] * RAD_TO_PI), this->up[0], this->up[1], this->up[2]);
		glRotatef((float)(this->rotate[0] * RAD_TO_PI), this->right[0] , this->right[1] , this->right[2]);
		glRotatef((float)(this->rotate[2] * RAD_TO_PI), this->front[0] , this->front[1] , this->front[2]);

		glScalef(this->scale[0], this->scale[1], this->scale[2]);

		glDisable(GL_LIGHTING);	// Just use colours.

		glmDraw(this->model, GLM_TEXTURE | GLM_MATERIAL);

	glPopMatrix();	// Restore world coordinate system.
}

void Piece::RotateX(double angle)
{
	float x = this->right[0];
	float y = this->right[1];
	float z = this->right[2];

	this->right[0] = x;
	this->right[1] = cosf(angle)*y - sinf(angle)*z;
	this->right[2] = sinf(angle)*y + cosf(angle)*z;

	this->rotate[0] += angle;
}

void Piece::RotateY(double angle)
{
	float x = this->up[0];
	float y = this->up[1];
	float z = this->up[2];

	this->up[0] = cosf(angle)*x + sinf(angle)*z;
	this->up[1] = y;
	this->up[2] = -sinf(angle)*x + cosf(angle)*z;

	this->rotate[1] += angle;
}

void Piece::RotateZ(double angle)
{
	float x = this->front[0];
	float y = this->front[1];
	float z = this->front[2];

	this->front[0] = cosf(angle)*x - sinf(angle)*y;
	this->front[1] = sinf(angle)*x + cosf(angle)*y;
	this->front[2] = z;

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

Piece::~Piece(void)
{
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