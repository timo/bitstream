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

void setup_opengl( const int &Width, const int &Height, const int &bpp );

int process_events(GLPlayer &Player1);

void quit_program( const int &code );



//================================== main() ===========================

int main(int argc,char * argv[])
{

  GLint width, height, bpp, die = 0;
  //  GLdouble fps, time, cleartime;
  SDL_Surface *Surface;

  GLPlayer Player1(0,0,-10);

  width = 1024;
  height = 768;
  bpp = 0;

  //Initialize SDL
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_ShowCursor(0);

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
  Surface = SDL_SetVideoMode(width, height, 0, SDL_OPENGL);

  if ( Surface == NULL ) {
    fprintf(stderr, "Unable to create OpenGL screen: %s\n", SDL_GetError());
    SDL_Quit();
    exit(2);
  }

  SDL_WM_SetCaption("Bitstream", NULL);

  setup_opengl( width, height, bpp );

  Player1.setVel(0);

  while(!die)
    {

      
      GLDraw(Player1);

      die = process_events(Player1);
      
      if(die == 2){

	SDL_WM_ToggleFullScreen(Surface);

	die=0;
      }
    }
      

 if(SDL_JoystickOpened(0))
    SDL_JoystickClose(joy);


  cout << "\nEnd of main()" << endl;
  SDL_FreeSurface(Surface);
  SDL_Quit();
  return 0;

}



