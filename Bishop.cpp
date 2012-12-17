#include "Bishop.h"


Bishop::Bishop(void): Piece("bishop","bishop")//"kakugyo")//"letters/b")//
{
	glmScale(this->model,0.020);
	this->TranslateZ(-0.5);
	this->RotateX(3.14/2);
	this->RotateY(-3.14/2);
}


Bishop::~Bishop(void)
{
}

void Bishop::Animate()
{
	this->angle += 1.0;
	this->SetSizeZ((1 + sin(angle)/10));
}
