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

/////////////////////////////// Public ///////////////////////////////////////

//============================= Lifecycle ====================================

static GLuint m_uTotal = 0;

static GLdouble m_dXtilt;
static GLdouble m_dYtilt;

GLEntity::GLEntity(const GLdouble &x, const GLdouble &y, const GLdouble &z)
  :m_dX(x),
   m_dY(y),
   m_dZ(z)
{

#ifdef DEBUG
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

#ifdef DEBUG
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

/////////////////////// XYZ Set Functions ////////////////////

GLint 
GLEntity::shift(const GLdouble &xvel,const GLdouble &yvel, const GLdouble &zvel )
{
  if(m_idraw==1){

  m_dThisTime = SDL_GetTicks();

  if(m_dX < 5 && m_dX > -5 || (m_dX >= 5 && xvel <=0) 
     || (m_dX <= -5 && xvel >=0)){ 
    m_dX += (m_dThisTime-m_dLastTime)/1000 * xvel;
  }
  
  if(m_dY < 4 && m_dY > -2.5 || (m_dY >= 4 && yvel <=0) 
     || (m_dY <= -2.5 && yvel >=0)){ 
    m_dY += (m_dThisTime-m_dLastTime)/1000 * yvel;
  }
  m_dZ += (m_dThisTime-m_dLastTime)/1000 * zvel;

  m_dLastTime = m_dThisTime;

  }
  else{

    m_dLastTime = SDL_GetTicks();
    m_idraw =1;

  }
  return 0;
}

void 
GLEntity::tilt(const GLdouble &x, const GLdouble &y){

  m_dXtilt = x;
  m_dYtilt = -y*(0.5);

}


//============================= Access      ==================================

GLdouble 
GLEntity::getX()const{
  return m_dX;
}

GLdouble 
GLEntity::getY()const{
  return m_dY;
}

GLdouble 
GLEntity::getZ()const{
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

//============================= Inquiry    ===================================
/////////////////////////////// Protected Methods ////////////////////////////

/////////////////////////////// Private   Methods ////////////////////////////
