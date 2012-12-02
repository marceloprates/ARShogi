#pragma once
#include "piece.h"
class Pawn :
	public Piece
{
public:
	Pawn(void);
	~Pawn(void);

	virtual void Animate();
};

