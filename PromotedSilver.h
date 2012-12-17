#pragma once
#include "piece.h"
class PromotedSilver :
	public Piece
{
public:
	PromotedSilver(void);
	~PromotedSilver(void);

	virtual void Animate();
};

