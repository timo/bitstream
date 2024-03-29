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

using namespace std;
//extern GLuint texture[];
//extern GLuint sky[];

extern Texture gndSkin;
extern Texture skySkin;
/////////////////////////////// Public ///////////////////////////////////////
const double DEFAULTSPEED = 100;
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
GLMap::draw(GLdouble speed)const{

  static GLdouble dZ=0, dSky=0;
  static GLdouble thistime, lasttime=0, second;

  thistime= (double)SDL_GetTicks();

  if(lasttime == 0){
    lasttime = thistime;
    second = 0;
    dZ = (double)lasttime/1000;
  }
  
  glRotatef(this->getXtilt(), 0.0f, 0.0f, 1.0f);
  glRotatef(this->getYtilt(), 1.0f, 0.0f, 0.0f);
      
  
    
  dZ += speed*((double)(thistime-lasttime)/1000)/50;
  //  cout << dZ << endl;
  dSky += (double)(thistime-lasttime)/100000;
  if(dZ > 1){ dZ = 0; second = thistime;}
  if(dSky > 10){ dSky = 0; }


      glEnable(GL_TEXTURE_2D);

      glBindTexture(GL_TEXTURE_2D, gndSkin.getID());

      glDisable(GL_LIGHTING);
      // 

      glBegin(GL_QUADS);  // Ground
      int x=0;
      for(int z=0; z <= 20; z++  ){
	
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
      
      glEnd();
      
      // Funny looking code so that the sky moves slower

      glDisable(GL_DEPTH_TEST);
      glBindTexture(GL_TEXTURE_2D, skySkin.getID());  // Sky
      glBegin(GL_QUADS);

      glColor3f(1.0f, 1.0f, 1.0f);
      glNormal3f(0.0f, -1.0f, 0.0f);
      glTexCoord2f(0.0f+dSky, 0.0f+dSky*4);
      glVertex3f(-150.0f, 40.0f, 0.0f);
      glTexCoord2f(0.0f+dSky, 1.0f+dSky*4);
      glVertex3f(-150.0f, -5.0f, -95.0f);
      glTexCoord2f(1.0f+dSky, 1.0f+dSky*4);
      glVertex3f(150.0f, -5.0f, -95.0f);
      glTexCoord2f(1.0f+dSky, 0.0f+dSky*4);
      glVertex3f(150.0f, 40.0f, 0.0f);

      glEnd();
      glDisable(GL_TEXTURE_2D);

      glEnable(GL_LIGHTING);

      //  glFlush();

      glEnable(GL_DEPTH_TEST);
      lasttime = SDL_GetTicks();

}

//============================= Access      ==================================
//============================= Inquiry   ===================================
/////////////////////////////// Protected Methods ////////////////////////////

/////////////////////////////// Private   Methods ////////////////////////////
