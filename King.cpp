#include "King.h"


King::King(void): Piece("king","o")
{
	this->RotateX(3.14/2);
	this->RotateY(3.14/2);
}


King::~King(void)
{
}
