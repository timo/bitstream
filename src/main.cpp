#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <math.h>


#include "GLEntity.h"
#include "GLPlayer.h"
#include "GLMap.h"

/** 
  * Jeff Mrochuk 
  * Nov 2, 2001
  * @description 
  * 
  */
using namespace std; 	//introduces namespace std



int GLDraw(const GLPlayer &);

void setup_opengl( const int &Width, const int &Height );

int process_events(GLPlayer &Player1);

void quit_program( const int &code );

//================================== main() ===========================

int main(int argc,char * argv[])
{

  GLint width, height, bpp, n, die = 0;
  GLdouble fps, time, cleartime;


  GLPlayer Player1(0, 0, -10);

  width = 1024;
  height = 768;
  bpp = 32;

  //Initialize SDL
  SDL_Init(SDL_INIT_EVERYTHING);

  //Initialize Joystick

  SDL_Joystick *joy;
  // Check for joystick
  if(SDL_NumJoysticks()>0){
    // Open joystick
    joy=SDL_JoystickOpen(0);
  
    if(joy)
      {
	cout << "Opened Joystick 0" << endl;
	cout << "Name: " << SDL_JoystickName(0) << endl;
	cout << "Number of Axes: " << SDL_JoystickNumAxes(joy) << endl;
	cout << "Number of Buttons: "<<  SDL_JoystickNumButtons(joy) << endl;;
	cout << "Number of Balls: "<< SDL_JoystickNumBalls(joy) << endl;
      }
    else
      cout << "Couldn't open Joystick 0" << endl;
 
  }  
  else
    {
      cout << "No Joysticks found" << endl;
    }

  SDL_JoystickEventState(SDL_ENABLE);

  //Initialize window

  if ( SDL_SetVideoMode(width, height, 0, SDL_OPENGL) == NULL ) {
    fprintf(stderr, "Unable to create OpenGL screen: %s\n", SDL_GetError());
    SDL_Quit();
    exit(2);
  }

  SDL_WM_SetCaption("Judecca's StarFox Ripoff", NULL);

  SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
  SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
  SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
  SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, bpp );
  SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

  setup_opengl( width, height );

  Player1.setVel(0);

  while(!die)
    {
      n=n+1;
      die = process_events(Player1);
      GLDraw(Player1);
      // FPS Calcs
      if(time>5000){
      
      cleartime=SDL_GetTicks();
      n=0;
      }
      time=SDL_GetTicks()-cleartime;
      fps=(GLfloat)n/time*1000;
      fprintf(stderr,"\r%f",fps);
      
      
    }
      

 if(SDL_JoystickOpened(0))
    SDL_JoystickClose(joy);


  cout << "\nEnd of main()" << endl;
  return 0;

}



