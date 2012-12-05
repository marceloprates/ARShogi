#include "GoldGeneral.h"
#include <math.h>


GoldGeneral::GoldGeneral(void): Piece("gold_general","kin")
{
	this->RotateX(-3.14/2);
}


GoldGeneral::~GoldGeneral(void)
{
}

void GoldGeneral::Animate()
{
	this->RotateY(0.1);
}
