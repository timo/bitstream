/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: t; c-basic-offset: 3 -*- */

#ifndef _hud_h_
#define _hud_h_

#include <GL/gl.h>

void DrawHud();

const GLdouble HUD_LEFT_BG = 0.5;
const GLdouble HUD_RIGHT_BG = 1.0;
const GLdouble HUD_LEFT_FG = 0.51;
const GLdouble HUD_RIGHT_FG = 0.99;

const GLdouble HUD_HEALTH_TOP_BG = 0.75;
const GLdouble HUD_HEALTH_BOTTOM_BG = 0.70;
const GLdouble HUD_HEALTH_TOP_FG = 0.74;
const GLdouble HUD_HEALTH_BOTTOM_FG = 0.71;
const GLdouble HUD_HEALTH_DIFF = HUD_RIGHT_FG - HUD_LEFT_FG;

const GLdouble HUD_ENERGY_TOP_BG = 0.68;
const GLdouble HUD_ENERGY_BOTTOM_BG = 0.63;
const GLdouble HUD_ENERGY_TOP_FG = 0.67;
const GLdouble HUD_ENERGY_BOTTOM_FG = 0.64;
const GLdouble HUD_ENERGY_DIFF = HUD_RIGHT_FG - HUD_LEFT_FG;

const GLdouble HUD_SPEED_TOP_BG = 0.61;
const GLdouble HUD_SPEED_BOTTOM_BG = 0.56;
const GLdouble HUD_SPEED_TOP_FG = 0.60;
const GLdouble HUD_SPEED_BOTTOM_FG = 0.57;
const GLdouble HUD_SPEED_DIFF = HUD_RIGHT_FG - HUD_LEFT_FG;

#endif // _hud_h_
