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
#include <vector>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include "Texture.h"
#include "BSM.h"

using namespace std;
/////////////////////////////// Public ///////////////////////////////////////

//============================= Lifecycle ====================================

static const GLdouble ACCEL = 0.25;
static const GLdouble SLOW = 0.125;
static const GLdouble DRIFT = 0; //0.0625;
static const GLdouble MAXSPEED = 80;
static const GLdouble DEGTORAD = 0.017453278;
static const GLdouble RECHARGE_FACTOR = 20;



GLPlayer::GLPlayer(const GLdouble &x, const GLdouble &y, const GLdouble &z)
  :GLEntity(x, y, z),
   m_dLasttime(0),
   m_dEnergy(100),
   m_dDamage(100),
   hitTime(0)
{

#ifdef DEBUG
  cout << "GLPlayer created" << endl;
#endif
 m_model.LoadBSM ("data/player/player.bsm");
  m_dOverrideY=0;
  m_dOverrideX=0;
  m_dVelocity = 40;
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
GLPlayer::draw(){

  //glLoadIdentity();



  glPushMatrix();

  glTranslatef(this->getX(),this->getY(),this->getZ());


  glRotatef(-(this->getXtilt()*2), 0.0f, 1.0f, 0.0f);
  glRotatef(-(this->getYtilt()), 0.0f, 0.0f, 1.0f);

  if(m_dOverrideY == 0){
    glRotatef((double)m_dYvel*0.2, 1.0f, 0.0f, 0.0f);
  }


  glColor4f(0.2f, 0.2f, 0.2f, 0.8f);

  m_model.draw();

  glPopMatrix();



}


void
GLPlayer::collide(){

  double y_Lheight, xwing, ywing;
  double y_Rheight, y_Fheight, nose;

  // Fix this 
  ywing = 2*cos(-m_dXvel*0.3*DEGTORAD*2);
  xwing = 2*sin(-m_dXvel*0.3*DEGTORAD*2);
  nose = 6*sin(m_dYvel*0.2*DEGTORAD*2);

  y_Lheight = this->getY() - xwing - ywing;
  y_Rheight = this->getY() + xwing - ywing;
  y_Fheight = this->getY() + nose;

    
}

void 
GLPlayer::move(const GLint &x, const GLint &y, const GLint &z){

  if(!m_dLasttime){ m_dLasttime= (double)SDL_GetTicks();}

  GLdouble deltatime =( (double)SDL_GetTicks() - m_dLasttime);

  m_dLasttime = (double)SDL_GetTicks();

  // X Speed manipulation

  if(x==1){


    if(m_dXvel < MAXSPEED){
      m_dXvel += ACCEL*deltatime;
    }
    
  }
  
  if(x==0 && m_dXvel > 0){
    m_dXvel -= SLOW*deltatime;
  }
  else if(x==0 && m_dXvel < 0){
    m_dXvel += SLOW*deltatime;
  }
  else if(x==0 && m_dXvel == 0){
    m_dXvel = 0;
  }
  
  if(x==-1){
    
    if(m_dXvel > -MAXSPEED){
       m_dXvel -= ACCEL*deltatime;
    }
    
  }
  
  
  // Y Speed manipulation
  
  //Override

  if(m_dOverrideY != 0){


    m_dYvel += m_dOverrideY;

    if(m_dYvel > MAXSPEED){
      m_dOverrideY = -2*deltatime;
    }

    if( fabs(m_dYvel) <  1.0 ){
      m_dOverrideY=0;
    }

  }

  //Normal Operatin
  else{

    if(y==1){
      
      if(m_dYvel < MAXSPEED){
	m_dYvel += ACCEL*deltatime;
      }
      
    }
    
    if(y==0 && m_dYvel > 0){
      m_dYvel -= SLOW*deltatime;
    }
    else if(y==0 && m_dYvel < -DRIFT){
      m_dYvel += SLOW*deltatime;

      

    }
    else if(y==0 && m_dYvel == 0){
      
      m_dYvel -= DRIFT*deltatime;

    }
    
    if(y==-1){
      
      if(m_dYvel > -MAXSPEED){
	m_dYvel -= ACCEL*deltatime;

	}
      
    }
    
  }
  
  

  // power recharge

  m_dEnergy += RECHARGE_FACTOR * deltatime/1000;
  if(m_dEnergy > 100){
    m_dEnergy = 100;
  }

//   if (this->getX() == -5){
//     this->tilt(MAXSPEED, m_dYvel);
//   }
//   else if(this->getX() == 5){
//     this->tilt(MAXSPEED, m_dYvel);
//   }
//   else{
//     this->tilt(m_dXvel, m_dYvel);
//   }

  this->tilt(this->getX()*16, m_dYvel,  this->getX()*15 );

  this->shift(m_dXvel, m_dYvel);


  
}




void 
GLPlayer::setVel(const GLdouble &x, const GLdouble &y){

  m_dXvel = x;
  m_dYvel = y;

}

void 
GLPlayer::SetPosition(const GLdouble &x, const GLdouble &y, const GLdouble &z){
  
  this->setX(x);
  this->setY(y);
  this->setZ(z);

}

bool
GLPlayer::isAlive(){

  if(m_model.getDamage() > 0) return true;

  return false;

}

GLdouble
GLPlayer::GetEnergy(){

  return m_dEnergy;

}

GLdouble
GLPlayer::GetDamage(){

  return m_model.getDamage();

}


void
GLPlayer::SetDamage(const GLdouble& damage){

  m_model.setDamage(damage);

}

int
GLPlayer::DrawEnergy(const GLdouble &energy){

  if(m_dEnergy <= energy){
    
    return 0;
  }

  m_dEnergy -= energy;


  return 1;

}
GLdouble
GLPlayer::GetLongestRadius(){


  return 2.236;
  //  return m_model.GetLongestRadius();

}

void 
GLPlayer::ApplyDamage(const GLdouble &hit){
#ifdef VERBOSE
  cout << "About to damage model" << endl;
#endif
  m_model.hit(hit);

}

GLdouble 
GLPlayer::GetHitDamage(){

  return m_dDamage;
}


bool
GLPlayer::isPlayer(){

  return true;

}

GLdouble
GLPlayer::GetVelocity(){
  // cout << m_dVelocity << endl;
  return m_dVelocity;

}

void
GLPlayer::SpeedUp(){

  m_dVelocity += 0.05*( (double)SDL_GetTicks()- m_dLasttime);
  if(m_dVelocity > 100){ m_dVelocity = 100; };
}


void
GLPlayer::SlowDown(){

  m_dVelocity -= 0.05*((double)SDL_GetTicks() - m_dLasttime );
  if(m_dVelocity < 10){m_dVelocity = 10; };
}
 

//============================= Access      ==================================



//============================= Inquiry    ===================================
/////////////////////////////// Protected Methods ////////////////////////////

/////////////////////////////// Private   Methods ////////////////////////////
