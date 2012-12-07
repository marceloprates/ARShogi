#include "Rook.h"


Rook::Rook(void): Piece("rook","hi")
{
	glmScale(this->model,0.20);
	this->RotateX(3.14/2);
}


Rook::~Rook(void)
{
}

void Rook::Animate()
{
	this->RotateZ(0.1);
}