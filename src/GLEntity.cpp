
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
// Name: GLEntity 
//
// Files:
// Bugs:
// See Also:
// Type: C++-Source
//////////////////////////////////////////////////////////////////////////
// Authors:  Jeff Mrochuk jm@v-wave.com
// Date:     Nov 2, 2001
//////////////////////////////////////////////////////////////////////////
// Modifications:
//
/////////////////////////////////////////////////////////////////////////
#include "GLEntity.h"                                // class implemented
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>

using namespace std;
/////////////////////////////// Public ///////////////////////////////////////

//============================= Lifecycle ====================================



GLEntity::GLEntity(const GLdouble &x, const GLdouble &y, const GLdouble &z)
  :m_dX(x),
   m_dY(y),
   m_dZ(z)
{

#ifdef VERBOSE
  cout << "GLEntity created" << endl;
#endif

  m_uTotal += 1;

}// GLEntity


GLEntity::GLEntity(const position& pos)
  :m_dX(pos.x),
   m_dY(pos.y),
   m_dZ(pos.z)
{

#ifdef VERBOSE
  cout << "GLEntity created" << endl;
#endif

  m_uTotal += 1;

}// GLEntity

GLEntity::GLEntity(const GLEntity&)
{

#ifdef DEBUG
  cout << "GLEntity copied " << endl;
#endif

}// GLEntity

GLEntity::~GLEntity()
{

#ifdef VERBOSE
  cout << "GLEntity destroyed" << endl;
#endif

}// ~GLEntity


//============================= Operators ====================================

GLEntity& 
GLEntity::operator=(const GLEntity&rhs)
{
   if ( this==&rhs ) {
        return *this;
    }
    //superclass::operator =(rhs);

    //add local assignments

    return *this;

}// =

//============================= Operations ===================================

////////////////////////////drawAll////////////////////////////////////////

void 
GLEntity::drawAll()const{

  cout << "This is where the drawing of entities would be done" << endl;

}

void 
GLEntity::draw(){

  cout << "This is where the drawing of entities would be done" << endl;

}
/////////////////////// XYZ Set Functions ////////////////////

GLint 
GLEntity::shift(const GLdouble &xvel,const GLdouble &yvel, const GLdouble &zvel )
{
  if(m_idraw==1){
      
      m_dThisTime = (double)SDL_GetTicks();
      //    }

    if(m_dX < 5 && m_dX > -5 || (m_dX >= 5 && xvel <=0) 
       || (m_dX <= -5 && xvel >=0)){ 
      m_dX += (m_dThisTime-m_dLastTime)/1000 * xvel/10;
    }
  
    if(m_dY < 4 && m_dY > -2.5 || (m_dY >= 4 && yvel <=0) 
       || (m_dY <= -2.5 && yvel >=0)){ 
      m_dY += (m_dThisTime-m_dLastTime)/1000 * yvel/10;
    }
    m_dZ += (m_dThisTime-m_dLastTime)/1000 * zvel/10;
  
    m_dLastTime = m_dThisTime;
    
  }
  else{
    
    m_dLastTime = SDL_GetTicks();
    m_idraw =1;

  }
  return 0;
}

void 
GLEntity::tilt(const GLdouble &x, const GLdouble &y, const GLdouble &z){
  m_dXtilt = x/10.0;
  m_dYtilt = -y*(0.05);
  m_dZtilt = z;
}
 

//============================= Access      ==================================

GLdouble 
GLEntity::getX(){
  return m_dX;
}

GLdouble 
GLEntity::getY(){
  return m_dY;
}

GLdouble 
GLEntity::getZ(){
  return m_dZ;
}

GLdouble 
GLEntity::getXtilt()const{
  return m_dXtilt;
}

GLdouble 
GLEntity::getYtilt()const{
  return m_dYtilt;
}


GLdouble 
GLEntity::GetLongestRadius(){
  return 0;
}

void 
GLEntity::ApplyDamage(const GLdouble &){

}
	
GLdouble 
GLEntity::GetHitDamage(){
  return 0;
}

bool
GLEntity::isPlayer(){

  return false;

}
//============================= Inquiry    ===================================
/////////////////////////////// Protected Methods ////////////////////////////

/////////////////////////////// Private   Methods ////////////////////////////
