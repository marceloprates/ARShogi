#include "GoldGeneral.h"
#include <math.h>


GoldGeneral::GoldGeneral(void): Piece("gold_general","gold")//"kin")//"letters/g")//
{
	glmScale(this->model,0.5);
	this->RotateZ(2.0*3.14);
}

GoldGeneral::~GoldGeneral(void)
{
}

void GoldGeneral::Animate()
{
	this->angle += 1.0;
	this->SetSizeZ((1 + sin(angle)/10));
}
