
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <math.h>


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


//BSM player;

BSM player;

vector < GLEntity * > entityptr;
GLPlayer *playerptr;

unsigned entitysize;

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

    for(unsigned i=0; i < entitysize; i++){  // Draw the entities!
      entityptr[i]->draw();
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

  entitysize=0;

  glClearColor(0.67f, 0.70f, 0.76f, 0.0f);        
  glClearDepth(1.0);                         

  glEnable(GL_TEXTURE_2D);	
 
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
 
  // Fog stuff

  glFogi(GL_FOG_MODE, GL_LINEAR);
  glFogfv(GL_FOG_COLOR, fogColor);
  glFogf(GL_FOG_DENSITY, 1.0);
  glHint(GL_FOG_HINT, GL_DONT_CARE);
  glFogf(GL_FOG_START, 50.0);
  glFogf(GL_FOG_END, 95.0);
  glEnable(GL_FOG);

}



