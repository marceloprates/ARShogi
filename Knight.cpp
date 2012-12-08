#include "Knight.h"


Knight::Knight(void): Piece("knight","kei")
{
	glmScale(this->model,0.025);
	this->TranslateY(0.5);
}

Knight::~Knight(void)
{
}

void Knight::Animate()
{
	this->angle += 1.0;
	this->SetSizeZ((1 + sin(angle)/10));
}
