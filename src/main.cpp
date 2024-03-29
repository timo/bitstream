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
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <math.h>

#include "events.h"
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



int GLDraw(GLPlayer &);

void setup_opengl( const int &Width, const int &Height, const int &bpp );

int process_events();

void quit_program( const int &code );




//================================== main() ===========================

int main(int argc,char * argv[])
{

  GLint width, height, bpp, die = 0;
  SDL_Surface *Surface;
  const SDL_VideoInfo* info = NULL;
  bool fullscreen;
  Uint32 *flags = new Uint32;

  // Defaults
  fullscreen=false;
  width = 800;
  height = 600;

  if(argc>1){

    for(int i = 1; i < argc; i++){


      if(!strcmp(argv[i],"--window")){
	fullscreen = false;
	continue;
      }
      if(!strcmp(argv[i],"--fullscreen")){
	fullscreen = true;
	continue;
      }
      if(!strcmp(argv[i],"--width")){
	width = atoi(argv[i+1]);
	i++;  // Skip the next one
	continue;
      }
      if(!strcmp(argv[i],"--height")){
	height = atoi(argv[i+1]);
	i++;  // Skip the next one
	continue;
      }
      if(!strcmp(argv[i],"--help") || (argv[i][0] != '-')){
	cout << endl;
	cout << "Bitstream command line options:" << endl;
	cout << "   --window\t\tRun in windowed mode"<< endl;
	cout << "   --fullscreen\t\tRun in fullscreen mode (default)" << endl;
	cout << "   --width\t\tSpecify X resolution (default 1024)" << endl;
	cout << "   --height\t\tSpecify Y resolution (default 768)" << endl;
	cout << endl;
	return 0;
      }

    }
  }

  //Initialize SDL
  if(  SDL_Init(SDL_INIT_EVERYTHING)< 0) 
    {
#ifdef __linux__
         fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
#endif
      exit(1);
    }


  info = SDL_GetVideoInfo( );
  bpp = info->vfmt->BitsPerPixel;

  atexit(SDL_Quit);
  
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


  SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
  SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 6 );
  SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
  SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
  SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );


  //Initialize window
  if(fullscreen){
    *flags = SDL_OPENGL | SDL_FULLSCREEN;
  }else{
    *flags = SDL_OPENGL;
  }

  Surface = SDL_SetVideoMode(width, height, bpp, *flags);

  if ( Surface == NULL ) {
#ifdef __linux__
    fprintf(stderr, "Unable to create OpenGL screen: %s\n", SDL_GetError());
#endif
    SDL_Quit();
    exit(2);
  }

  SDL_WM_SetCaption("Bitstream Pre-Alpha", NULL);

  setup_opengl( width, height, bpp );

  GLPlayer Player1(0,0,-11);
  Player1.setVel(0);



  while(!die)
    {
      
      GLDraw(Player1);

      die = process_events();
      
      if(die == 2){
	if(fullscreen){
	  *flags=SDL_OPENGL;
	  fullscreen=false;
	}
	else{
	  *flags = SDL_OPENGL | SDL_FULLSCREEN;
	  fullscreen = true;
	}
        Surface = SDL_SetVideoMode(width, height, bpp, *flags);
	die=0;
      }
    }
      

 if(SDL_JoystickOpened(0))
    SDL_JoystickClose(joy);


  cout << "\nEnd of main()" << endl;

  SDL_Quit();
  return 0;

}



