/*
   Bitstream:  An OpenGL Space Action Game
   http://icculus.org/bitstream/

   Copyright (C) 2001, 2002 Jeff Mrochuk
   
   This file is part of bitstream.     Bitstream is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.     
   
   Bitstream is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.     
   You should have received a copy of the GNU General Public License along with Bitstream; if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

Jeff Mrochuk
jm@icculus.org

*/

//////////////////////////////////////////////////////////////////////////
// Name: en_weapon 
//
// Files:
// Bugs:
// See Also:
// Type: C++-Source
//////////////////////////////////////////////////////////////////////////
// Authors:
// Date:
//////////////////////////////////////////////////////////////////////////
// Modifications:
//
/////////////////////////////////////////////////////////////////////////
#include "en_weapon.h"                                // class implemented
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <math.h>
#include "Texture.h"
#include "BSM.h"
#include "GLPlayer.h"
#include "physics.h"
#include "effects.h"

using namespace std;

static const GLdouble DEGTORAD = 0.017453278;
static const GLdouble HIT_RADIUS = 0.00;
extern GLPlayer *playerptr;

/////////////////////////////// Public ///////////////////////////////////////

//============================= Lifecycle ====================================

en_weapon::en_weapon(const GLdouble&x, const GLdouble&y, const GLdouble&z)
  :m_Vel(50),
   m_xAngle(0),
   m_yAngle(0),
   m_rho(0),
   m_dDamage(10),
   m_HitGround(0),
   m_lastTime(0)
{
  m_SourceExplosion = 0;

  m_xBase = x;
  m_yBase = y;
  m_zBase = z;

  m_model.LoadBSM ("data/player/shot.bsm");
  m_model.SetMainDamage(5);
  
}// en_weapon


en_weapon::en_weapon(const en_weapon&)
{
}// en_weapon

en_weapon::~en_weapon()
{
  int expl_id = 0;
  position hit;
  hit.x = m_xPos + m_xBase;
  hit.y = m_yPos + m_yBase;
  hit.z = m_zPos + m_zBase;

  // explosion(hit, 0.5, 0.5, expl_id);
  expl_id = 0;
  particle_explosion(hit, 2, 0.5, expl_id);
}// ~en_weapon


//============================= Operators ====================================

en_weapon& 
en_weapon::operator=(const en_weapon&rhs)
{
   if ( this==&rhs ) {
        return *this;
    }
    //superclass::operator =(rhs);

    //add local assignments

    return *this;

}// =

//============================= Operations ===================================

void 
en_weapon::draw(){


  position  hit;

  if(!m_lastTime){
    m_lastTime=SDL_GetTicks(); 

    m_xAngle = 0;
    m_yAngle = 0;
   
  }

  glPushMatrix();
  m_yPos = m_rho*sin(m_xAngle*DEGTORAD);
  m_xPos = -m_rho*cos(m_xAngle*DEGTORAD)*sin(m_yAngle*DEGTORAD);
  m_zPos = -m_rho*cos(m_yAngle*DEGTORAD)*cos(m_xAngle*DEGTORAD);

  // cout << m_xBase << "," << m_yBase << endl;

  m_rho -= (double)(SDL_GetTicks() - m_lastTime)/1000 * m_Vel;

  // yAngle is 

  //  hit.x = m_xPos + m_xBase;
  hit.y = m_yPos + m_yBase;


  if(hit.y < -5){  // hits the ground

     m_rho=200;  // Effectively destroy itself
		   
  }    


   glTranslatef(m_xBase, m_yBase, m_zBase);

   glRotatef(m_xAngle, 1.0f, 0.0f, 0.0f);
   glRotatef(m_yAngle, 0.0f, 1.0f, 0.0f);
   glTranslatef(0.0f, 0.0f, -m_rho);


  glColor3f(0.5f, 0.2f, 0.0f);
  m_model.draw();


  glPopMatrix();
  m_lastTime = SDL_GetTicks();


}


GLdouble
en_weapon::getRho()const{

  return m_rho;
}


GLdouble 
en_weapon::GetLongestRadius(){

  // return  m_model.GetLongestRadius();
  return HIT_RADIUS;
}


//============================= Access      ==================================
//============================= Inquiry    ===================================

bool 
en_weapon::isAlive(){

  //  cout << m_model.getDamage() << endl;
  if( (m_rho > 195) || (m_model.getDamage() <= 0 )) return false;
  
  return true;
  
}

GLdouble 
en_weapon::getX(){

  return m_xPos + m_xBase;

}

GLdouble 
en_weapon::getY(){

  return m_yPos + m_yBase;
}

GLdouble 
en_weapon::getZ(){
  return m_zPos + m_zBase;

}

void 
en_weapon::ApplyDamage(const GLdouble &damage){

  m_model.hit(damage);

}

GLdouble 
en_weapon::GetHitDamage(){

  return m_dDamage;

}





/////////////////////////////// Protected Methods ////////////////////////////

/////////////////////////////// Private   Methods ////////////////////////////
