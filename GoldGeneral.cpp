#include "GoldGeneral.h"
#include <math.h>


GoldGeneral::GoldGeneral(void): Piece("gold_general","kin")
{
	glmScale(this->model,0.5);
	this->RotateZ(1.5*3.14);
}

GoldGeneral::~GoldGeneral(void)
{
}

void GoldGeneral::Animate()
{
}
