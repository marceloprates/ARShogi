#include "Rook.h"


Rook::Rook(void): Piece("rook","rook")//"hisha")//"letters/r")//
{
	glmScale(this->model,0.20);
	this->RotateX(3.14/2);
}


Rook::~Rook(void)
{
}

void Rook::Animate()
{
	this->RotateY(0.1);
}