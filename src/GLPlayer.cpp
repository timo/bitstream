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
#include "MD2.h"
#include "Texture.h"
#include "BSM.h"

/////////////////////////////// Public ///////////////////////////////////////

//============================= Lifecycle ====================================

static const GLint ACCEL = 1;
static const GLint SLOW = 1;
static const GLint MAXSPEED = 80;

extern BSM player;
extern Texture playerSkin;

GLPlayer::GLPlayer(const GLdouble &x, const GLdouble &y, const GLdouble &z)
  :GLEntity(x, y, z)
{

#ifdef DEBUG
  cout << "GLPlayer created" << endl;
#endif

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

   glRotatef(-(double)m_dXvel*0.3, 0.0f, 0.0f, 1.0f);
   glRotatef((double)m_dYvel*0.3, 1.0f, 0.0f, 0.0f);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, playerSkin.getID());

  //  glScalef(0.05f, 0.05f, 0.05f);

  player.draw();

  glDisable(GL_TEXTURE_2D);

  glPopMatrix();



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

  if(y==1){

    if(m_dYvel < MAXSPEED){
    m_dYvel += ACCEL;
    }

  }

  if(y==0 && m_dYvel > 0){
    m_dYvel -= SLOW;
  }
  else if(y==0 && m_dYvel < 0){
    m_dYvel += SLOW;
  }
  else if(y==0 && m_dYvel == 0){
    m_dYvel = 0;
  }

  if(y==-1){

    if(m_dYvel > -MAXSPEED){
      m_dYvel -= ACCEL;
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
