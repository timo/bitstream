/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: t; c-basic-offset: 3 -*- */

// Effects header file

#ifndef _effects_h_
#define _effects_h_

#include "Texture.h"

extern Texture spark;

void process_effects();

int explosion(const position&pos, const double &radius, const double&duration,int index);

int particle_explosion(const position &source, const double &speed, const double &duration, int index);

#endif // _effects_h_
