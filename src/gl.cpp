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

//Too many includes.

#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#ifdef __linux__
 #include <GL/glx.h>
#endif

#include <SDL/SDL.h>
#include <math.h>
#include <string>
#include <deque>
#include <list>
#include <iterator>

#include "GLEntity.h"
#include "GLPlayer.h"
#include "GLMap.h"
#include "GLShot.h"
#include "Texture.h"
#include "BSM.h"
#include "en_cube.h"
#include "hud.h"
#include "collision.h"
#include "effects.h"
#include "text.h"
#include <typeinfo>

using namespace std;


//UGLY GLOBALS


// GLuint  base; /* Base Display List For The Font Set */
list < GLEntity * > entityptr;
list< GLEntity * >::iterator entityiter, entityiter2;
unsigned entitysize;
GLPlayer *playerptr;
Texture gndSkin;
Texture skySkin;
Texture text;
Texture spark;
// GLuint texture[3];
// GLuint sky[3];


//========================== GLDraw() ===================================


int GLDraw(GLPlayer &Player1){

  static GLMap map1;
  static Uint32 Frames;
  static Uint32 lasttime;
  static Uint32 cubetime;
  GLfloat seconds;
  static GLfloat fps;
  static int once = 0;
  static int once_really = 0;
  static int cubedeaths=0;

  playerptr = &Player1;

  if(once_really == 0){
    entityiter=entityptr.end();
    *entityiter = playerptr;
    entityptr.push_back(*entityiter);

    once_really = 1;


  }

  if(SDL_GetTicks() - cubetime > 3000){
    once = 0;
  }
  
   if(once==0){
     entityiter=entityptr.end();
     *entityiter = new en_cube(0, 0, -200);
     entityptr.push_back(*entityiter);
     cubetime = SDL_GetTicks();
     once = 1;

   }

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();

  glMatrixMode(GL_MODELVIEW);

  glPushMatrix();  // Things affected by perspective

  map1.draw(1.00);

  process_effects();

  for (entityiter=entityptr.begin();entityiter!=entityptr.end();entityiter++){

    (*entityiter)->draw();
    // Check for collisions
    for (entityiter2=entityiter;entityiter2!=entityptr.end();entityiter2++){

      if(entityiter!=entityiter2){
	  if(!strcmp("en_cube", (typeid(**entityiter2).name()+1) )){
	    cubedeaths = (*entityiter2)->GetDestroyed();
	  }
	if(SphericalHit(**entityiter, **entityiter2)){
	  (*entityiter2)->ApplyDamage((*entityiter)->GetHitDamage()); 
	  (*entityiter)->ApplyDamage((*entityiter2)->GetHitDamage()); 
	  if(!((*entityiter2)->isAlive())){
	    if(!((*entityiter2)->isPlayer())){
	      delete *entityiter2;
	    }
	    entityptr.erase(entityiter2--);  // Take it out of the list
	  }
	}
      }
    }
    
    if(!((*entityiter)->isAlive())){
      if(!((*entityiter)->isPlayer())){

	delete *entityiter;
      }
      entityptr.erase(entityiter--);  // Take it out of the list
    } 


  }



  glPopMatrix();

  if(!(playerptr->isAlive())){
    glColor4f(1.0, 0.2, 0.2, 1.0);
    glPrint(320, 380, 0, "Press SPACE to fail again, loser");
    glPrint(320, 360, 0, "     You scored %d kills", cubedeaths);
  }
  

  //TEXT
  //  glLoadIdentity( );
  // glColor4f(1.0, 1.0, 1.0, 1.0);
	
  DrawHud();

  glColor4f(1.0, 1.0, 1.0, 1.0);
  glPrint(20, 40, 0, "CUBES WASTED: %d", cubedeaths);
  glPrint(20, 20 , 0, "BITSTREAM: ATTACK OF THE CUBES");
  glPrint(920, 20, 0, "FPS: %3.0f", fps);
  //FPS
  Frames++;
  {
    GLint t = SDL_GetTicks();
    if (t - lasttime >= 1000) {
      seconds = (GLfloat)(t - lasttime) / 1000.0;
      fps = (GLfloat)Frames / (GLfloat)seconds;
      lasttime = t;
      Frames = 0;
    }
  }

  glFlush();
  SDL_GL_SwapBuffers();

  return 0;

}

//========================== setup_opengl() ===============================

void setup_opengl( const int &Width, const int &Height , const int &bpp)
{


  //Textures
  //  playerSkin.LoadPCX ("data/player/player.pcx", GL_LINEAR, GL_LINEAR);
  text.LoadBMP("data/font.bmp",  GL_LINEAR, GL_LINEAR);
  gndSkin.LoadBMP("data/ground.bmp", GL_LINEAR, GL_LINEAR);
  skySkin.LoadBMP("data/sky.bmp", GL_LINEAR, GL_LINEAR);
  spark.LoadBMP("data/spark.bmp", GL_LINEAR, GL_LINEAR);

  glEnable(GL_DEPTH_TEST); 
  glDepthMask(GL_TRUE); 
  glDepthFunc(GL_LESS); 

  glViewport(0, 0, Width, Height); 

  entitysize=0;
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClearDepth(1.0);
                   
  glShadeModel(GL_SMOOTH);                                 
  glMatrixMode(GL_PROJECTION);

  glLoadIdentity(); 

  GLfloat mat_ambient[]=  { 0, 0, 0, 1.0};
  GLfloat mat_specular[]=  { 0.0, 0.0, 0.0, 1.0};
  GLfloat mat_shininess[] = { 50.0 };

  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

  GLfloat LightAmbient[]=	   { 0.5f, 0.5f, 0.5f, 1.0f };
  GLfloat LightDiffuse[]=	   { 0.5f, 0.5f, 0.5f, 1.0f };
  GLfloat LightPosition[]=	   { 0.0f, 10.0f, -20.0f, 1.0f };

  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
  glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);		
  glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
  glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);

  glLoadIdentity();                            
  gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);    

  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);
	
  glBlendFunc(GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA);

  glEnable(GL_BLEND);


  glPolygonMode (GL_FRONT, GL_FILL);
  glPolygonMode (GL_BACK, GL_FILL);

  // glCullFace( GL_BACK );
  // glFrontFace( GL_CCW );
  // glEnable( GL_CULL_FACE );

	
  // glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_amb);

  BuildFont();

  //  glBlendFunc(GL_SRC_ALPHA,GL_SRC_COLOR);


  glEnable(GL_LIGHT1);	
  glEnable(GL_LIGHTING);

  glEnable(GL_COLOR_MATERIAL);

  // Fog stuff
  GLfloat fogColor []= {0.67f, 0.70f, 0.76f, 1.0f};
  glFogi(GL_FOG_MODE, GL_LINEAR);
  glFogfv(GL_FOG_COLOR, fogColor);
  glFogf(GL_FOG_DENSITY, 1.0);
  glHint(GL_FOG_HINT, GL_DONT_CARE);
  glFogf(GL_FOG_START, 50.0);
  glFogf(GL_FOG_END, 95.0);
  glEnable(GL_FOG);

  glMatrixMode(GL_MODELVIEW);
}

