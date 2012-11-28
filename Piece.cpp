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

		glScalef(this->scale[0], this->scale[1], this->scale[2]);

		glDisable(GL_LIGHTING);	// Just use colours.

		glmDraw(this->model, GLM_TEXTURE | GLM_MATERIAL);

	glPopMatrix();	// Restore world coordinate system.
}

void Piece::Rotate(double angle, double x, double y, double z)
{

}

void Piece::RotateX(double angle)
{
	this->Rotate(angle, 1.0, 0.0, 0.0);
}

void Piece::RotateY(double angle)
{
	this->Rotate(angle, 0.0, 1.0, 0.0);
}

void Piece::RotateZ(double angle)
{
	this->Rotate(angle, 0.0, 0.0, 1.0);
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
