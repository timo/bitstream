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


extern GLPlayer *playerptr;

/////////////////////////////// Public ///////////////////////////////////////

//============================= Lifecycle ====================================

GLShot::GLShot()
  :m_Vel(1),
   m_xAngle(0),
   m_yAngle(0),
   m_rho(18),
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

  if(!m_lastTime){
    m_lastTime=SDL_GetTicks(); 
    m_xBase = playerptr->getX();
    m_yBase = playerptr->getY();
    //    m_xAngle = -playerptr->getYtilt();
    //    m_yAngle = -playerptr->getXtilt();
  }

  m_rho += (SDL_GetTicks() - m_lastTime)/20.0 * m_Vel;

  glTranslatef(m_xBase, m_yBase, 0.0f);
  glRotatef(m_xAngle, 1.0f, 0.0f, 0.0f);
  glRotatef(m_yAngle, 0.0f, 1.0f, 0.0f);
  glTranslatef(0.0f, 0.0f, -m_rho);

  glColor3f(0.2f, 0.0f, 0.5f);
  shot.draw();

  glTranslatef(0.0f, 0.0f, m_rho);
  glRotatef(-m_yAngle, 0.0f, 1.0f, 0.0f);
  glRotatef(-m_xAngle, 1.0f, 0.0f, 0.0f);
  glTranslatef(-m_xBase, -m_yBase, 0.0f);

  m_lastTime = SDL_GetTicks();


}


GLdouble
GLShot::getRho()const{

  return m_rho;
}


//============================= Access      ==================================
//============================= Inquiry    ===================================
/////////////////////////////// Protected Methods ////////////////////////////

/////////////////////////////// Private   Methods ////////////////////////////
