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
// Name: GLPlayer 
//
// Files:
// Bugs:
// See Also:
// Type: C++-Source
//////////////////////////////////////////////////////////////////////////
// Authors: Jeff Mrochuk
// Date:    Nov 2, 2001
//////////////////////////////////////////////////////////////////////////
// Modifications:
//
/////////////////////////////////////////////////////////////////////////
#include "GLPlayer.h" 
                               // class implemented
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include "Texture.h"
#include "BSM.h"

/////////////////////////////// Public ///////////////////////////////////////

//============================= Lifecycle ====================================

static const GLint ACCEL = 1;
static const GLint SLOW = 1;
static GLdouble DRIFT = 0.5;
static const GLint MAXSPEED = 80;
static const GLdouble DEGTORAD = 0.0349066;

extern BSM player;
extern Texture playerSkin;

GLPlayer::GLPlayer(const GLdouble &x, const GLdouble &y, const GLdouble &z)
  :GLEntity(x, y, z),
   hitTime(0)
{

#ifdef DEBUG
  cout << "GLPlayer created" << endl;
#endif
  m_dOverrideY=0;
  m_dOverrideX=0;

}// GLPlayer

GLPlayer::GLPlayer(const GLPlayer&)
{
}// GLPlayer

GLPlayer::~GLPlayer()
{
#ifdef DEBUG
  cout << "GLPlayer destroyed" << endl;
#endif

}// ~GLPlayer


//============================= Operators ====================================

GLPlayer& 
GLPlayer::operator=(const GLPlayer&rhs)
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
GLPlayer::draw()const{

  //glLoadIdentity();



  glPushMatrix();

  glTranslatef(this->getX(),this->getY(),this->getZ());


  glRotatef(-(double)m_dXvel*0.2, 0.0f, 1.0f, 0.0f);
  glRotatef(-(double)m_dXvel*0.3, 0.0f, 0.0f, 1.0f);

  if(m_dOverrideY == 0){
    glRotatef((double)m_dYvel*0.2, 1.0f, 0.0f, 0.0f);
  }


  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, playerSkin.getID());

  glColor4f(0.31f, 0.35f, 0.45f, 0.8f);

  player.draw();

  glDisable(GL_TEXTURE_2D);

  if(!m_collide)
    {
      glDisable(GL_BLEND);
    }
  if(m_collide){
    
    glColor4f(1.0f,1.0f,1.0f,1.0f);
    glEnable(GL_BLEND);

  }
  
  glPopMatrix();



}


void
GLPlayer::collide(){

  double y_Lheight, xwing, ywing;
  double y_Rheight, y_Fheight, nose;


  ywing = 2*cos(-m_dXvel*0.3*DEGTORAD);
  xwing = 2*sin(-m_dXvel*0.3*DEGTORAD);
  nose = 6*sin(m_dYvel*0.2*DEGTORAD);

  y_Lheight = this->getY() - xwing - ywing;
  y_Rheight = this->getY() + xwing - ywing;
  y_Fheight = this->getY() + nose;

  //Collision flash
  if(m_collide){
    m_collide+=1;
    if(m_collide>3) m_collide=0;
  }

  //ground collision

  if(hitTime+500 < SDL_GetTicks()){
    if(y_Lheight < -5.0)
      {
	m_dOverrideY = 8;
	if(m_collide==0){  
	  m_collide=1;
	  player.hit(4);
	  hitTime=SDL_GetTicks();
	}
      }
    
    if(y_Rheight < -5.0)
      {
	m_dOverrideY = 8;
	if(m_collide==0){
	  m_collide=1;
	  player.hit(3); 
	  hitTime=SDL_GetTicks();
	}
	
      }
    
    if(y_Fheight < -5.0)
      {
	m_dOverrideY = 8;
	if(m_collide==0) {
	  m_collide=1;
	  player.hit(0);
	  hitTime=SDL_GetTicks();
	}
      }
  }
    
}

void 
GLPlayer::move(const GLint &x=0, const GLint &y=0, const GLint &z=0){

  // X Speed manipulation

  if(x==1){
    
    //FIXME acceleration may be different on some machines

    if(m_dXvel < MAXSPEED){
      m_dXvel += ACCEL;
    }
    
  }
  
  if(x==0 && m_dXvel > 0){
    m_dXvel -= SLOW;
  }
  else if(x==0 && m_dXvel < 0){
    m_dXvel += SLOW;
  }
  else if(x==0 && m_dXvel == 0){
    m_dXvel = 0;
  }
  
  if(x==-1){
    
    if(m_dXvel > -MAXSPEED){
       m_dXvel -= ACCEL;
    }
    
  }
  
  
  // Y Speed manipulation
  
  //Override

  if(m_dOverrideY != 0){


    m_dYvel += m_dOverrideY;

    if(m_dYvel > MAXSPEED){
      m_dOverrideY = -2;
    }

    if( fabs(m_dYvel) <  0.7 ){
      m_dOverrideY=0;
    }

  }

  //Normal Operatin
  else{

    if(y==1){
      
      if(m_dYvel < MAXSPEED){
	m_dYvel += ACCEL;
      }
      
    }
    
    if(y==0 && m_dYvel > 0){
      m_dYvel -= SLOW;
    }
    else if(y==0 && m_dYvel < -DRIFT){
      m_dYvel += SLOW;

      

    }
    else if(y==0 && m_dYvel == 0){
      
      m_dYvel -= DRIFT;

    }
    
    if(y==-1){
      
      if(m_dYvel > -MAXSPEED){
	m_dYvel -= ACCEL;

	}
      
    }
    
  }
  
  

  this->tilt(m_dXvel, m_dYvel);


  this->shift(m_dXvel, m_dYvel);


  
}


void 
GLPlayer::setVel(const GLdouble &x, const GLdouble &y){

  m_dXvel = x;
  m_dYvel = y;

}

//============================= Access      ==================================



//============================= Inquiry    ===================================
/////////////////////////////// Protected Methods ////////////////////////////

/////////////////////////////// Private   Methods ////////////////////////////
