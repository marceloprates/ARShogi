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

class Piece
{
public:

	const char*	patt_path;
	double		patt_width;
	double		patt_centre[2];
	double		patt_trans[3][4];
	int			patt_found;
	int			patt_id;

	Piece(char* model_name, char* patt_name);
	~Piece(void);

	void Draw();

	void RotateX(double angle);
	void RotateY(double angle);
	void RotateZ(double angle);

	void Scale(double sx, double sy, double sz);
	void Scale(double factor);
	void ScaleX(double s);
	void ScaleY(double s);
	void ScaleZ(double s);
	void SetSize(double sx, double sy, double sz);
	void SetSize(double s);
	void SetSizeX(double s);
	void SetSizeY(double s);
	void SetSizeZ(double s);

	void Translate(double tx, double ty, double tz);
	void TranslateX(double t);
	void TranslateY(double t);
	void TranslateZ(double t);
	void SetPosition(double x, double y, double z);
	void SetPositionX(double x);
	void SetPositionY(double y);
	void SetPositionZ(double z);

	void Jump();
	void Rotate();
	virtual void Animate();
double right[3];
	double up[3];
	double front[3];

protected:

	GLMmodel* model;

	double rotate[3];
	double scale[3];
	double translate[3];

	double angle;

	void Init(char* model_name, char* patt_name);
	static int setupMarker(const char *patt_name, int *patt_id);

	void Rotate(double axis[3], double vector[3], double angle);
	
};

