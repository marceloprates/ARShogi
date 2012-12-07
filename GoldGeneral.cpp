#include "GoldGeneral.h"
#include <math.h>


GoldGeneral::GoldGeneral(void): Piece("gold_general","kin")
{
	glmScale(this->model,0.5);
}


GoldGeneral::~GoldGeneral(void)
{
}

void GoldGeneral::Animate()
{
	this->RotateY(0.1);
}
