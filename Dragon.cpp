#include "Dragon.h"


Dragon::Dragon(void): Piece("dragon","dragon")//"ryuo")//"letters/r")//
{
	//glmScale(this->model,0.20);
	this->RotateX(3.14/2);
	this->RotateY(-3.14/2);
}


Dragon::~Dragon(void)
{
}

void Dragon::Animate()
{
	this->angle += 1.0;
	this->SetSizeY((1 + sin(angle)/10));
	this->SetPositionY((1.0 + sin(angle/1.5))/4);
}
