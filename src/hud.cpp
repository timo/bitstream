#include "hud.h"
#include "GLPlayer.h"
#include "BSM.h"
#include <GL/gl.h>

extern BSM player;
void DrawHealthBar(){

  GLdouble healthfactor, health;
  healthfactor = player.getDamage()/100.0;
  health = HUD_LEFT_FG + HUD_HEALTH_DIFF*healthfactor;

  glPushMatrix();
  glDisable(GL_LIGHTING);
  glBegin(GL_TRIANGLES);
  glColor4f(0.2, 0.2, 0.2, 1.0);

  glVertex3f(HUD_LEFT_BG, HUD_HEALTH_TOP_BG, -1);
  glVertex3f(HUD_RIGHT_BG, HUD_HEALTH_TOP_BG, -1);
  glVertex3f(HUD_LEFT_BG, HUD_HEALTH_BOTTOM_BG, -1);

  glVertex3f(HUD_RIGHT_BG, HUD_HEALTH_BOTTOM_BG, -1);
  glVertex3f(HUD_RIGHT_BG, HUD_HEALTH_TOP_BG, -1);
  glVertex3f(HUD_LEFT_BG, HUD_HEALTH_BOTTOM_BG, -1);

  glColor4f(0.8, 0.2, 0.2, 1.0);

  glVertex3f(HUD_LEFT_FG, HUD_HEALTH_TOP_FG, -0.999);
  glColor4f(0.8, 0.8, 0.8, 1.0);
  glVertex3f(health, HUD_HEALTH_TOP_FG, -0.999);
  glColor4f(0.8, 0.2, 0.2, 1.0);
  glVertex3f(HUD_LEFT_FG,HUD_HEALTH_BOTTOM_FG , -0.999);
  glColor4f(0.8, 0.8, 0.8, 1.0);
  glVertex3f(health, HUD_HEALTH_BOTTOM_FG, -0.999);
  glVertex3f(health, HUD_HEALTH_TOP_FG, -0.999);
  glColor4f(0.8, 0.2, 0.2, 1.0);
  glVertex3f(HUD_LEFT_FG, HUD_HEALTH_BOTTOM_FG, -0.999);

  glEnd();
  glEnable(GL_LIGHTING);
  glPopMatrix();
}

void DrawEnergyBar(){
  GLdouble energyfactor, energy;
  // healthfactor = player.getDamage()/100.0;
  energyfactor = 1.0;
  energy = HUD_LEFT_FG + HUD_ENERGY_DIFF*energyfactor;

  glPushMatrix();
  glDisable(GL_LIGHTING);
  glBegin(GL_TRIANGLES);
  glColor4f(0.2, 0.2, 0.2, 1.0);

  glVertex3f(HUD_LEFT_BG, HUD_ENERGY_TOP_BG, -1);
  glVertex3f(HUD_RIGHT_BG, HUD_ENERGY_TOP_BG, -1);
  glVertex3f(HUD_LEFT_BG, HUD_ENERGY_BOTTOM_BG, -1);

  glVertex3f(HUD_RIGHT_BG, HUD_ENERGY_BOTTOM_BG, -1);
  glVertex3f(HUD_RIGHT_BG, HUD_ENERGY_TOP_BG, -1);
  glVertex3f(HUD_LEFT_BG, HUD_ENERGY_BOTTOM_BG, -1);

  glColor4f(0.2, 0.2, 0.8, 1.0);

  glVertex3f(HUD_LEFT_FG, HUD_ENERGY_TOP_FG, -0.999);
  glColor4f(0.8, 0.8, 0.8, 1.0);
  glVertex3f(energy, HUD_ENERGY_TOP_FG, -0.999);
  glColor4f(0.2, 0.2, 0.8, 1.0);
  glVertex3f(HUD_LEFT_FG,HUD_ENERGY_BOTTOM_FG , -0.999);
  glColor4f(0.8, 0.8, 0.8, 1.0);
  glVertex3f(energy, HUD_ENERGY_BOTTOM_FG, -0.999);
  glVertex3f(energy, HUD_ENERGY_TOP_FG, -0.999);
  glColor4f(0.2, 0.2, 0.8, 1.0);
  glVertex3f(HUD_LEFT_FG, HUD_ENERGY_BOTTOM_FG, -0.999);

  glEnd();
  glEnable(GL_LIGHTING);
  glPopMatrix();


}

void DrawHud(){
  DrawHealthBar();
  DrawEnergyBar();
  
}
