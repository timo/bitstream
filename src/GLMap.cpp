//////////////////////////////////////////////////////////////////////////
// Name: GLMap 
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
#include "GLMap.h"                                // class implemented
#include <iostream>
#include <SDL/SDL.h>
extern GLuint texture[];


/////////////////////////////// Public ///////////////////////////////////////

//============================= Lifecycle ====================================

GLMap::GLMap(const int &iMapnum)
  : GLEntity()
{
}// GLMap

GLMap::GLMap(const GLMap&)
{
}// GLMap

GLMap::~GLMap()
{
}// ~GLMap


//============================= Operators ====================================

GLMap& 
GLMap::operator=(const GLMap&rhs)
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
GLMap::draw()const{

  static GLdouble dZ=0;
  static GLuint thistime, lasttime=0;
  thistime=SDL_GetTicks();
  if(lasttime != 0)
    {

      glPushMatrix();

      glRotatef(this->getXtilt(), 0.0f, 0.0f, 1.0f);
      glRotatef(this->getYtilt(), 1.0f, 0.0f, 0.0f);
      
      glEnable(GL_TEXTURE_2D);
      glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
      glBindTexture(GL_TEXTURE_2D, texture[2]);


      // FIXME This lighting doesn't even make sense

      glBegin(GL_QUADS);
      int x=0;
      for(int z=0; z <= 20; z++  ){
    
	glColor3f(z*0.1f+0.2f, z*0.1f+0.2f, z*0.1f+0.2f);
	
	glNormal3f(0.0f, 1.0f, 0.0f);
      
	glTexCoord2f(0.0f, 0.0f+x*0.1+dZ);    
	glVertex3f(-150.0f, -5.0f, z*(-5.0f));
	glTexCoord2f(5.0f, 0.0f+x*0.1+dZ);    
	glVertex3f( 150.0f, -5.0f, z*(-5.0f));

	glColor3f(z*0.1f+ 0.25f, z*0.1f+0.25f, z*0.1f+0.25f);

	glTexCoord2f(5.0f, 0.1f+x*0.1+dZ);    
	glVertex3f( 150.0f, -5.0f, z*(-5.0f)-5.0f);
	glTexCoord2f(0.0f, 0.1f+x*0.1+dZ);  
	glVertex3f(-150.0f, -5.0f, z*(-5.0f)-5.0f);
	x++;
	if(x==10){x=0;}
      }
      
      
      
      
      glColor3f(1.0f, 1.0f, 1.0f);
      glNormal3f(0.0f, 0.0f, 1.0f);
      glVertex3f(-150.0f, -5.0f, -95.0f);
      glVertex3f(150.0f, -5.0f, -95.0f);
      glVertex3f(150.0f, 10.0f, -95.0f);
      glVertex3f(-150.0f, 10.0f, -95.0f);
      
      dZ+=((GLdouble)thistime - lasttime ) /1000;
      
      glEnd();
      glDisable(GL_TEXTURE_2D);
      glFlush();
      glPopMatrix();
    }
  lasttime = SDL_GetTicks();

}

//============================= Access      ==================================
//============================= Inquiry   ===================================
/////////////////////////////// Protected Methods ////////////////////////////

/////////////////////////////// Private   Methods ////////////////////////////
