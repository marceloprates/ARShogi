#include "PromotedSilver.h"


PromotedSilver::PromotedSilver(void): Piece("promoted_silver","silver+")//"ginsho+")//"letters/s")//
{
	glmScale(this->model,1.0);
	this->RotateX(3.14/2);
}


PromotedSilver::~PromotedSilver(void)
{
}

void PromotedSilver::Animate()
{
	this->angle += 1.0;
	this->SetSizeZ((1 + sin(angle)/10));
}
