#include "Horse.h"


Horse::Horse(void): Piece("horse","horse")//"ryuma")//"letters/r")//
{
	glmScale(this->model,0.025);
	this->TranslateY(0.5);
	this->RotateZ(-3.14/2);
}


Horse::~Horse(void)
{
}

void Horse::Animate()
{
	this->angle += 1.0;
	this->SetSizeZ((1 + sin(angle)/10));
}
