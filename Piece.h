#pragma once

#include <stdio.h>
#include <stdlib.h>					// malloc(), free()
#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif
#include <AR/config.h>
#include <AR/video.h>
#include <AR/param.h>			// arParamDisp()
#include <AR/ar.h>
#include <AR/gsub_lite.h>
#include <math.h>

#include "glm.h"

enum PieceType
{
	King,
	Rook,
	Bishop,
	Gold_general,
	Silver_general,
	Knight,
	Lance,
	Pawn,
	Gabumon
};

class Piece
{
public:

	Piece(GLMmodel* model);
	Piece(char* address);
	Piece(PieceType pieceType);
	~Piece(void);

	void Draw();

	void RotateX(double angle);
	void RotateY(double angle);
	void RotateZ(double angle);

	void Scale(double sx, double sy, double sz);
	void Scale(double factor);

	void Translate(double tx, double ty, double tz);
	void TranslateX(double t);
	void TranslateY(double t);
	void TranslateZ(double t);

private:

	GLMmodel* model;

	double right[3];
	double up[3];
	double front[3];

	double rotate[3];
	double scale[3];
	double translate[3];
	
};

