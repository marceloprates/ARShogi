#pragma once
#include "piece.h"
class Horse :
	public Piece
{
public:
	Horse(void);
	~Horse(void);

	virtual void Animate();
};

