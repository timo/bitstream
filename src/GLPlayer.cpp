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
static const GLdouble DRIFT = 0.5;
static const GLint MAXSPEED = 80;
static const GLdouble DEGTORAD = 0.0349066;

extern BSM player;
extern Texture playerSkin;

GLPlayer::GLPlayer(const GLdouble &x, const GLdouble &y, const GLdouble &z)
  :GLEntity(x, y, z)
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

  if(y_Lheight < -5.0)
    {
      m_dOverrideY = 8;
      if(m_collide==0)  m_collide=1;
    }

  if(y_Rheight < -5.0)
    {
      m_dOverrideY = 8;
      if(m_collide==0)  m_collide=1;
    }

  if(y_Fheight < -5.0)
    {
      m_dOverrideY = 8;
      if(m_collide==0)  m_collide=1;
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

    if( abs(m_dYvel) <  0.5 ){
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
