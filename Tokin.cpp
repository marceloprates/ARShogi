#include "Tokin.h"


Tokin::Tokin(void): Piece("tokin","tokin")//"fuhyo")//"letters/p")//
{
	glmScale(this->model,1.3);
	this->RotateX(3.14/2);
	this->RotateY(3.14/2);
	this->TranslateZ(0.8);
}

Tokin::~Tokin(void)
{
}

void Tokin::Animate()
{
	this->angle += 1.0;
	this->SetSizeY((1 + sin(angle)/5));
}
