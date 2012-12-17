#include "SilverGeneral.h"


SilverGeneral::SilverGeneral(void): Piece("silver_general","silver")//"ginsho")//"letters/s")//
{
	glmScale(this->model,0.5);
	this->RotateZ(3.14);
}


SilverGeneral::~SilverGeneral(void)
{
}

void SilverGeneral::Animate()
{
	this->angle += 1.0;
	this->SetSizeZ((1 + sin(angle)/10));
}
