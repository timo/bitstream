/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: t; c-basic-offset: 3 -*- */

#ifndef _collision_h_
#define _collision_h_

#include <GL/gl.h>
#include "GLEntity.h"
#include "BSM.h"

GLdouble LongestRadius(BSM &bsm);
bool SphericalHit(GLEntity &object1, GLEntity &object2);

#endif // _collision_h_
