
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <math.h>


#include "GLEntity.h"
#include "GLPlayer.h"
#include "GLMap.h"


static GLfloat LightAmbient[]=	   { 0.5f, 0.5f, 0.5f, 1.0f };
static GLfloat LightDiffuse[]=	   { 1.0f, 1.0f, 1.0f, 1.0f };
static GLfloat LightPosition[]=	   { 0.0f, 20.0f, 0.0f, 1.0f };


//========================== GLDraw() ===================================


int GLDraw(const GLPlayer &Player1){

  static GLMap map1;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  map1.draw();
  Player1.draw();

  SDL_GL_SwapBuffers();
  return 0;

}

//========================== setup_opengl() ===============================

void setup_opengl( const int &Width, const int &Height )
{


  /*	float ratio = (float) Width / (float) Height; */

  glViewport(0, 0, Width, Height);
  glEnable(GL_TEXTURE_2D); 

  glClearColor(0.67f, 0.76f, 0.86f, 0.0f);        
  glClearDepth(1.0);                         
  glDepthFunc(GL_LESS);                       

  glLineWidth(10);                   

  glShadeModel(GL_SMOOTH);                   
  glMatrixMode(GL_PROJECTION);

  glLoadIdentity();                            
  gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);    

  glMatrixMode(GL_MODELVIEW);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

  glCullFace( GL_BACK );
  glFrontFace( GL_CCW );
  glEnable( GL_CULL_FACE );

  glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);		
  glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
  glLightfv(GL_LIGHT0, GL_POSITION,LightPosition);	
                                               
  //  glBlendFunc(GL_SRC_ALPHA,GL_ONE);

  glEnable(GL_BLEND);
  glEnable(GL_DEPTH_TEST); 
  glEnable(GL_LIGHT0);
  glEnable(GL_COLOR_MATERIAL);	
  glEnable(GL_LIGHTING);


}
