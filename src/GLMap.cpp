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
#include "Texture.h"
//extern GLuint texture[];
//extern GLuint sky[];

extern Texture gndSkin;
extern Texture skySkin;
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

  if(lasttime == 0)
    {
      
      lasttime = thistime;
      
    }


      glRotatef(this->getXtilt(), 0.0f, 0.0f, 1.0f);
      glRotatef(this->getYtilt(), 1.0f, 0.0f, 0.0f);
      
      glEnable(GL_TEXTURE_2D);
      glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
      // glBindTexture(GL_TEXTURE_2D, texture[2]);

      glBindTexture(GL_TEXTURE_2D, gndSkin.getID());
      // FIXME This lighting doesn't even make sense

      glBegin(GL_QUADS);
      int x=0;
      for(int z=0; z <= 20; z++  ){
    
	//	glColor3f(z*0.1f+0.2f, z*0.1f+0.2f, z*0.1f+0.2f);
	
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
      

      
      dZ+=((GLdouble)thistime - lasttime ) /800;
      
      glEnd();


      glBindTexture(GL_TEXTURE_2D, skySkin.getID());
      glBegin(GL_QUADS);

      glColor3f(1.0f, 1.0f, 1.0f);
      glNormal3f(0.0f, -1.0f, 0.0f);
      glTexCoord2f(0.0f+dZ/400, 0.0f+dZ/50);
      glVertex3f(-150.0f, 10.0f, 0.0f);
      glTexCoord2f(0.0f+dZ/400, 1.0f+dZ/50);
      glVertex3f(-150.0f, -5.0f, -95.0f);
      glTexCoord2f(1.0f+dZ/400, 1.0f+dZ/50);
      glVertex3f(150.0f, -5.0f, -95.0f);
      glTexCoord2f(1.0f+dZ/400, 0.0f+dZ/50);
      glVertex3f(150.0f, 10.0f, 0.0f);

      glEnd();
      glDisable(GL_TEXTURE_2D);
      glFlush();

      
      lasttime = SDL_GetTicks();

}

//============================= Access      ==================================
//============================= Inquiry   ===================================
/////////////////////////////// Protected Methods ////////////////////////////

/////////////////////////////// Private   Methods ////////////////////////////
