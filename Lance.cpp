#include "Lance.h"


Lance::Lance(void): Piece("lance","kyo")
{
	glmScale(this->model,0.05);
	this->RotateX(3.14/2);
	this->RotateY(3.14/2);
}


Lance::~Lance(void)
{
}
