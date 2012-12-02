#pragma once
#include "piece.h"
class Rook :
	public Piece
{
public:
	Rook(void);
	~Rook(void);

	virtual void Animate();
};

