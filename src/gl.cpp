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


#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <math.h>
#include <string>


#include "GLEntity.h"
#include "GLPlayer.h"
#include "GLMap.h"
#include "GLShot.h"
#include "Texture.h"
#include "BSM.h"


static GLfloat LightAmbient[]=	   { 1.0f, 1.0f, 1.0f, 1.0f };
static GLfloat LightDiffuse[]=	   { 1.0f, 1.0f, 1.0f, 1.0f };
static GLfloat LightPosition[]=	   { 0.0f, 0.0f, 10.0f, 1.0f };
static GLfloat mat_amb[]=          { 0.1, 0.5, 0.8, 1.0};
static GLfloat fogColor []= {0.67f, 0.70f, 0.76f, 1.0f};


//UGLY GLOBALS

//BSM player;
BSM player;
vector < GLEntity * > shotptr;
unsigned shotsize;
GLPlayer *playerptr;
Texture playerSkin;
Texture gndSkin;
Texture skySkin;
GLuint texture[3];
GLuint sky[3];

//========================== GLDraw() ===================================


int GLDraw(GLPlayer &Player1){

  static GLMap map1;

  playerptr = &Player1;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);


  glPushMatrix();  // Things affected by perspective
    map1.draw();

    for(unsigned i=0; i < shotsize; i++){  // Draw the firepower
      shotptr[i]->draw();

    }
				       
				       

  glPopMatrix();


  Player1.collide();  // Player stuff
  glEnable(GL_BLEND);
  Player1.draw();



  SDL_GL_SwapBuffers();

  return 0;

}

//========================== setup_opengl() ===============================

void setup_opengl( const int &Width, const int &Height , const int &bpp)
{


  //Textures
  //  playerSkin.LoadPCX ("data/player/player.pcx", GL_LINEAR, GL_LINEAR);
  gndSkin.LoadBMP("data/ground.bmp", GL_LINEAR, GL_LINEAR);
  skySkin.LoadBMP("data/sky.bmp", GL_LINEAR, GL_LINEAR);



  //BSM
  player.LoadBSM ("data/player/player.bsm");

  glViewport(0, 0, Width, Height); 

  shotsize=0;

  glClearColor(0.67f, 0.70f, 0.76f, 0.0f);        
  glClearDepth(1.0);                         

 
  glShadeModel(GL_SMOOTH);                     
                
  glMatrixMode(GL_PROJECTION);

  glLoadIdentity();                            
  gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);    

  glMatrixMode(GL_MODELVIEW);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

  //  glPolygonMode (GL_FRONT, GL_FILL);
  //  glPolygonMode (GL_BACK, GL_FILL);

  //   glCullFace( GL_BACK );
  //   glFrontFace( GL_CCW );
  //   glEnable( GL_CULL_FACE );

  glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);		
  glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
  glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);	
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_amb);


  glBlendFunc(GL_SRC_ALPHA,GL_SRC_COLOR);

  glEnable(GL_DEPTH_TEST); 

  glDepthFunc(GL_LEQUAL); 

  glEnable(GL_LIGHT1);
  glEnable(GL_COLOR_MATERIAL);	
  glEnable(GL_LIGHTING);

  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  glEnable(GL_COLOR_MATERIAL);
  // Fog stuff

  glFogi(GL_FOG_MODE, GL_LINEAR);
  glFogfv(GL_FOG_COLOR, fogColor);
  glFogf(GL_FOG_DENSITY, 1.0);
  glHint(GL_FOG_HINT, GL_DONT_CARE);
  glFogf(GL_FOG_START, 50.0);
  glFogf(GL_FOG_END, 95.0);
  glEnable(GL_FOG);

}

// Shamelessly stolen from Ti Leggett's SDL port of NeHe tutorial 13


// GLvoid KillFont( GLvoid )
// {
//     glDeleteLists( base, 96 );

//     return;
// }


// GLvoid buildFont( GLvoid )
// {
//     Display *dpy;          /* Our current X display */
//     XFontStruct *fontInfo; /* Our font info */

//     /* Sotrage for 96 characters */
//     base = glGenLists( 96 );

//     /* Get our current display long enough to get the fonts */
//     dpy = XOpenDisplay( NULL );

//     /* Get the font information */
//     fontInfo = XLoadQueryFont( dpy, "-adobe-helvetica-medium-r-normal--18-*-*-*-p-*-iso8859-1" );

//     /* If the above font didn't exist try one that should */
//     if ( fontInfo == NULL )
// 	{
// 	    fontInfo = XLoadQueryFont( dpy, "fixed" );
// 	    /* If that font doesn't exist, something is wrong */
// 	    if ( fontInfo == NULL )
// 		{
// 		    fprintf( stderr, "no X font available?\n" );
// 		    Quit( 1 );
// 		}
// 	}

//     /* generate the list */
//     glXUseXFont( fontInfo->fid, 32, 96, base );

//     /* Recover some memory */
//     XFreeFont( dpy, fontInfo );

//     /* close the display now that we're done with it */
//     XCloseDisplay( dpy );

//     return;
// }

// /* Print our GL text to the screen */
// GLvoid glPrint( const char *fmt, ... )
// {
//     char text[256]; /* Holds our string */
//     va_list ap;     /* Pointer to our list of elements */

//     /* If there's no text, do nothing */
//     if ( fmt == NULL )
// 	return;

//     /* Parses The String For Variables */
//     va_start( ap, fmt );
//       /* Converts Symbols To Actual Numbers */
//       vsprintf( text, fmt, ap );
//     va_end( ap );

//     /* Pushes the Display List Bits */
//     glPushAttrib( GL_LIST_BIT );

//     /* Sets base character to 32 */
//     glListBase( base - 32 );

//     /* Draws the text */
//     glCallLists( strlen( text ), GL_UNSIGNED_BYTE, text );

//     /* Pops the Display List Bits */
//     glPopAttrib( );
// }
