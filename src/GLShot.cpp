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
// Name: GLShot 
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
#include "GLShot.h"                                // class implemented
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include "Texture.h"
#include "BSM.h"
#include "GLPlayer.h"

using namespace std;

extern GLPlayer *playerptr;

/////////////////////////////// Public ///////////////////////////////////////

//============================= Lifecycle ====================================

GLShot::GLShot()
  :m_Vel(1),
   m_xAngle(0),
   m_yAngle(0),
   m_rho(0),
   m_lastTime(0)
{

  shot.LoadBSM ("data/player/shot.bsm");

}// GLShot

GLShot::GLShot(const GLShot&)
{
}// GLShot

GLShot::~GLShot()
{
}// ~GLShot


//============================= Operators ====================================

GLShot& 
GLShot::operator=(const GLShot&rhs)
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
GLShot::draw(){

  // This is ugly. Please don't harass me.

  if(!m_lastTime){
    m_lastTime=SDL_GetTicks(); 

    m_xBase = playerptr->getX() + playerptr->getXtilt()/3.0 ;
    m_yBase = playerptr->getY() - playerptr->getYtilt()/2.0 - (playerptr->getX())*(playerptr->getXtilt())/40.0;

    //   m_xAngle = -2.2*playerptr->getYtilt();
    //   m_yAngle = -playerptr->getXtilt();
    m_xAngle = -4.2*(playerptr->getYtilt());
    m_yAngle = -2.2*(playerptr->getXtilt()) ;
  }

  // cout << m_xBase << "," << m_yBase << endl;

    m_rho += (SDL_GetTicks() - m_lastTime)/20.0 * m_Vel;

  glTranslatef(0.0f, 0.0f, -18);

   glTranslatef(m_xBase, m_yBase, 0.0f);

  glRotatef(m_xAngle, 1.0f, 0.0f, 0.0f);
  glRotatef(m_yAngle, 0.0f, 1.0f, 0.0f);
  glTranslatef(0.0f, 0.0f, -m_rho);

  glColor3f(0.4f, 0.0f, 0.0f);
  shot.draw();
  glTranslatef(0.0f, 0.0f, m_rho);

  glRotatef(-m_yAngle, 0.0f, 1.0f, 0.0f);
  glRotatef(-m_xAngle, 1.0f, 0.0f, 0.0f);

   glTranslatef(-m_xBase, -m_yBase, 0.0f);

  glTranslatef(0.0f, 0.0f, 18);

  m_lastTime = SDL_GetTicks();


}


GLdouble
GLShot::getRho()const{

  return m_rho;
}


//============================= Access      ==================================
//============================= Inquiry    ===================================

bool 
GLShot::isAlive(){

  if( m_rho > 95 ) return false;

  return true;

}
/////////////////////////////// Protected Methods ////////////////////////////

/////////////////////////////// Private   Methods ////////////////////////////
