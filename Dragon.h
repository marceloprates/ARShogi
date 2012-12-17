#pragma once
#include "piece.h"
class Dragon :
	public Piece
{
public:
	Dragon(void);
	~Dragon(void);

	virtual void Animate();
};

