#pragma once
#include "piece.h"
class Bishop :
	public Piece
{
public:
	Bishop(void);
	~Bishop(void);

	virtual void Animate();
};

