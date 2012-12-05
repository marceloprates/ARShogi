#include "Gabumon.h"


Gabumon::Gabumon(void): Piece("gabumon","ryuo")
{
}


Gabumon::~Gabumon(void)
{
}

void Gabumon::Animate()
{
	this->angle += 1.0;
	this->SetSizeY((1 + sin(angle)/10));
	this->SetPositionY((1.0 + sin(angle/1.5))/4);
}