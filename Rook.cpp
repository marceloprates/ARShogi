#include "Rook.h"


Rook::Rook(void): Piece("rook","hi")
{
	glmScale(this->model,0.20);
}


Rook::~Rook(void)
{
}

void Rook::Animate()
{
	this->RotateZ(0.1);
}