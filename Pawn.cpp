#include "Pawn.h"


Pawn::Pawn(void): Piece("pawn","fu")
{
	glmScale(this->model,1.0);
	this->RotateX(3.14/2);
	this->RotateY(3.14);
	this->TranslateZ(0.5);
}

Pawn::~Pawn(void)
{
}

void Pawn::Animate()
{
	this->angle += 1.0;
	this->SetSizeY((1 + sin(angle)/5));
}