
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <math.h>


#include "GLEntity.h"
#include "GLPlayer.h"
#include "GLMap.h"


static GLfloat LightAmbient[]=	   { 0.2f, 0.2f, 0.2f, 1.0f };
static GLfloat LightDiffuse[]=	   { 1.0f, 1.0f, 1.0f, 1.0f };
static GLfloat LightPosition[]=	   { 0.0f, 10.0f, 10.0f, 1.0f };
static GLfloat mat_amb[]=          { 0.1, 0.5, 0.8, 1.0};

GLvoid LoadGLTextures();


GLuint texture[3];

//========================== GLDraw() ===================================


int GLDraw(const GLPlayer &Player1){

  static GLMap map1;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   map1.draw();
   Player1.draw();
   SDL_GL_SwapBuffers();

  //  SDL_GL_SwapBuffers();
  return 0;

}

//========================== setup_opengl() ===============================

void setup_opengl( const int &Width, const int &Height , const int &bpp)
{


  SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
  SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
  SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
  SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, bpp );
  SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

 
  LoadGLTextures();

  /*	float ratio = (float) Width / (float) Height; */

  glViewport(0, 0, Width, Height); 

  glClearColor(0.67f, 0.76f, 0.86f, 0.0f);        
  glClearDepth(1.0);                         

  glEnable(GL_TEXTURE_2D);	
 
  glShadeModel(GL_SMOOTH);                     

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
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_amb);
  // glBlendFunc(GL_SRC_ALPHA,GL_ONE);

  glEnable(GL_BLEND);
  glEnable(GL_DEPTH_TEST); 
  glDepthFunc(GL_LEQUAL); 
  glEnable(GL_LIGHT0);
  glEnable(GL_COLOR_MATERIAL);	
  glEnable(GL_LIGHTING);

  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
 


}


//========================= ImageLoad ===========================

SDL_Surface *ImageLoad(char *filename)
{
    Uint8 *rowhi, *rowlo;
    Uint8 *tmpbuf, tmpch;
    SDL_Surface *image;
    int i, j;

    image = SDL_LoadBMP(filename);
    if ( image == NULL ) {
        fprintf(stderr, "Unable to load %s: %s\n", filename, SDL_GetError());
        return(NULL);
    }

    /* GL surfaces are upsidedown and RGB, not BGR :-) */

    tmpbuf = new unsigned char[image->pitch];
    if ( tmpbuf == NULL ) 
      {
	fprintf(stderr, "Out of memory\n");
	return(NULL);
      }
    else
      {
	cout << "Alloc succeeded" << endl;
      }

    rowhi = (Uint8 *)image->pixels;
    rowlo = rowhi + (image->h * image->pitch) - image->pitch;

    for ( i=0; i<(image->h)/2; ++i ) {
      for ( j=0; j<(image->w); ++j ) {
	tmpch = rowhi[j*3];
	rowhi[j*3] = rowhi[j*3+2];
	rowhi[j*3+2] = tmpch;
	tmpch = rowlo[j*3];
	rowlo[j*3] = rowlo[j*3+2];
	rowlo[j*3+2] = tmpch;
      }

      memcpy(tmpbuf, rowhi, image->pitch);
      memcpy(rowhi, rowlo, image->pitch);
      memcpy(rowlo, tmpbuf, image->pitch);
      
      rowhi += image->pitch;
      rowlo -= image->pitch;
    }
    

    delete tmpbuf;

    return(image);
}

//=====================LoadGLTextures===========================

GLvoid LoadGLTextures()
{
 
    SDL_Surface *texture1;

    texture1 = ImageLoad("data/ground.bmp");
    if (!texture1) {
      SDL_Quit();
      exit(1);
    }
    
    glGenTextures(3, &texture[0]);

    glBindTexture(GL_TEXTURE_2D, texture[0]);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->w, texture1->h, 0, GL_RGB, GL_UNSIGNED_BYTE, texture1->pixels);
    
    // texture 2 (linear scaling)
    glBindTexture(GL_TEXTURE_2D, texture[1]);  
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
    glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->w, texture1->h, 0, GL_RGB, GL_UNSIGNED_BYTE, texture1->pixels);

    // texture 3 (mipmapped scaling)
    glBindTexture(GL_TEXTURE_2D, texture[2]);  

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST); 
    glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->w, texture1->h, 0, GL_RGB, GL_UNSIGNED_BYTE, texture1->pixels);

    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, texture1->w, texture1->h, GL_RGB, GL_UNSIGNED_BYTE, texture1->pixels);


}
