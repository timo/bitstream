/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: t; c-basic-offset: 3 -*- */

#ifndef _physics_h_
#define _physics_h_

#include <GL/gl.h>

const double X_LEFT_BOUND = -15;
const double X_RIGHT_BOUND = 15;

const double Y_TOP_BOUND = 5;
const double Y_BOTTOM_BOUND = -2;

const double Z_BACK_BOUND = -60;
const double Z_FRONT_BOUND = -30;
//Structs and function declarations for the physics
struct velocity{

	GLdouble x;
	GLdouble y;
	GLdouble z;

};

struct acceleration{

	GLdouble x;
	GLdouble y;
	GLdouble z;

};

struct position{

	GLdouble x;
	GLdouble y;
	GLdouble z;
	int boundaries;

};

struct rotation{

	GLdouble x;
	GLdouble y;
	GLdouble z;

};

void UpdateVelocity(velocity &v, const acceleration &a, const double &deltatime);
void UpdatePosition(position &p, const velocity& v, const double &deltatime);


#endif // _physics_h_
