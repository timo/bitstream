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

/////////////////////////////// Public ///////////////////////////////////////

//============================= Lifecycle ====================================

GLMap::GLMap(const int &iMapnum)
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



  glBegin(GL_TRIANGLES);

      glColor3f(0.1f, 0.1f, 0.2f);

      glNormal3f(0.0f, 1.0f, 0.0f);

      glVertex3f(-150.0f, -5.0f, 0.0f);
      glVertex3f( 150.0f, -5.0f, 0.0f);
      glColor3f(1.0f, 1.0f, 1.0f);
      glVertex3f(-150.0f, -5.0f, -100.0f);

      glNormal3f(0.0f, 1.0f, 0.0f);

      glColor3f(0.1f, 0.1f, 0.2f);

      glVertex3f( 150.0f, -5.0f, 0.0f);
      glColor3f(1.0f, 1.0f, 1.0f);
      glVertex3f( 150.0f, -5.0f, -100.0f);
      glVertex3f( -150.0f, -5.0f, -100.0f);

  glEnd();

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
