#include "SilverGeneral.h"


SilverGeneral::SilverGeneral(void): Piece("silver_general","gin")
{
	glmScale(this->model,0.5);
	this->RotateZ(3.14);
}


SilverGeneral::~SilverGeneral(void)
{
}
