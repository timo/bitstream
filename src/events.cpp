/*
 * Event code
 */

#include <SDL/SDL.h>
#include <iostream>

#include "GLEntity.h"
#include "GLPlayer.h"
#include "GLMap.h"	


int process_events(GLPlayer &Player1)
{

  static GLint x = 0 , y = 0 ;
  static GLint joyx, joyy;
  static GLint keyx, keyy;

  /*        SDL_Event event; */


  
  {
    SDL_Event event;

    while ( SDL_PollEvent(&event) ) {
      switch (event.type) {
	
      case SDL_MOUSEBUTTONDOWN:
	printf("Mouse button %d pressed at (%d,%d)\n",
	       event.button.button, event.button.x, event.button.y);
	break;

      case SDL_QUIT:
	return 1;

      case SDL_JOYAXISMOTION:

	if(event.jaxis.axis == 1 && event.jaxis.value < 0){
	  joyy=-1;   
	}

        if(event.jaxis.axis == 1 && event.jaxis.value > 0){
	  joyy=1;
	}

	if(event.jaxis.axis == 0 && event.jaxis.value > 0){
	  joyx=1;
	}

	if(event.jaxis.axis == 0 && event.jaxis.value < 0){
	  joyx=-1;
	}

	if(event.jaxis.axis == 0 && event.jaxis.value == 0){
	  joyx=0;
	}

	if(event.jaxis.axis == 1 && event.jaxis.value == 0){
	  joyy=0;
	}

	x=joyx;
	y=joyy;

	break;

      case SDL_KEYDOWN:

	if(event.key.state == SDL_PRESSED && event.key.keysym.sym == SDLK_LEFT){

	  keyx=-1;

	}

	if(event.key.state == SDL_PRESSED && event.key.keysym.sym == SDLK_RIGHT){

	  keyx=1;

	}

	if(event.key.state == SDL_PRESSED && event.key.keysym.sym == SDLK_UP){

	  keyy=-1;

	}

	if(event.key.state == SDL_PRESSED && event.key.keysym.sym == SDLK_DOWN){

	  keyy=1;

	}

	x=keyx;
	y=keyy;

	if(event.key.keysym.sym == SDLK_ESCAPE){
	  return 1;
	}

	if((event.key.keysym.sym == SDLK_RETURN) &&( ( event.key.keysym.mod == KMOD_LALT) || (event.key.keysym.mod == KMOD_RALT) ))
	  {	   

	    return 2; //Send video resize data.

	  }

	break;



      case SDL_KEYUP:

	if(event.key.keysym.sym == SDLK_LEFT){
	  if(keyx==-1){
	    keyx=0;}

	}

	if(event.key.keysym.sym == SDLK_RIGHT){
	  if(keyx==1){
	    keyx=0;}

	}

	if(event.key.keysym.sym == SDLK_UP){
	  if(keyy==-1){
	    keyy=0;}

	}

	if(event.key.keysym.sym == SDLK_DOWN){
	  if(keyy==1){
	    keyy=0;}

	}

	x=keyx;
	y=keyy;

      default:

	break;

      }
    }
  }

  /* Check current key state for special commands */

  Player1.move(x,y);

  return 0;

}
