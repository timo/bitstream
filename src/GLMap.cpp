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



  glPushMatrix();

  glRotatef(this->getXtilt(), 0.0f, 0.0f, 1.0f);
  glRotatef(this->getYtilt(), 1.0f, 0.0f, 0.0f);

  
  glEnable(GL_TEXTURE_2D);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
  glBindTexture(GL_TEXTURE_2D, texture[2]);
  glColor4f(1.0, 1.0, 1.0, 1.0);
  glBegin(GL_QUADS);

      glNormal3f(0.0f, 1.0f, 0.0f);
      glColor3f(0.1f, 0.1f, 0.2f);
  
          glTexCoord2f(0.0f, 0.0f);    
      glVertex3f(-150.0f, -5.0f, 0.0f);
          glTexCoord2f(10.0f, 0.0f);    
      glVertex3f( 150.0f, -5.0f, 0.0f);


      glColor3f(1.0f, 1.0f, 1.0f);
          glTexCoord2f(10.0f, 2.0f);    
      glVertex3f( 150.0f, -5.0f, -100.0f);
          glTexCoord2f(0.0f, 2.0f);  
      glVertex3f(-150.0f, -5.0f, -100.0f);


  glEnd();
  glFlush();
  glDisable(GL_TEXTURE_2D);

  

  glBegin(GL_LINES);



      glColor3f(1.0f,1.0f,1.0f);

      glVertex3f(-50.0f, 5.0f, 100.0f);
      glVertex3f( 50.0f, 5.0f, 100.0f);

  glEnd();

  glPopMatrix();

}

//============================= Access      ==================================
//============================= Inquiry   ===================================
/////////////////////////////// Protected Methods ////////////////////////////

/////////////////////////////// Private   Methods ////////////////////////////
