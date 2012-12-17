#include "King.h"


King::King(void): Piece("king","king")//"gyokusho")//"letters/k")//
{
	this->RotateX(3.14/2);
	this->RotateY(3.14);
}

void King::Animate()
{
	this->angle += 1.0;
	this->SetSizeY((1 + sin(angle)/10));
	this->SetPositionY((1.0 + sin(angle/1.5))/4);
}

King::~King(void)
{
}
