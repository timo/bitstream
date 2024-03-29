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


/*
 * Event code
 */

#include <SDL/SDL.h>
#include <iostream>
#include <list>
#include "GLEntity.h"
#include "GLPlayer.h"
#include "GLMap.h"
#include "GLShot.h"
#include "en_cube.h"	

using namespace std;

extern list < GLEntity * > entityptr;
extern list <GLEntity * >::iterator entityiter;
extern unsigned entitysize;
extern GLPlayer* playerptr;

int process_events()
{

  static GLint x = 0 , y = 0 ;
  static GLint joyx, joyy;
  static GLint keyx, keyy;
  static bool speedup = false;
  static bool slowdown = false;
  /*        SDL_Event event; */


  
  {
    SDL_Event event;

    while ( SDL_PollEvent(&event) ) {
      switch (event.type) {
	
      case SDL_MOUSEBUTTONDOWN:
	return 0;

      case SDL_QUIT:
	return 1;

      case SDL_JOYAXISMOTION:

	if(event.jaxis.axis && event.jaxis.value < -20000){
	  joyy=-1;   
	}

        if(event.jaxis.axis && event.jaxis.value > 20000){
	  joyy=1;
	}

	if(!event.jaxis.axis  && event.jaxis.value > 20000){
	  joyx=1;

	}

	if(!event.jaxis.axis && event.jaxis.value < -20000){
	  joyx=-1;
	}

	if(!event.jaxis.axis && (abs(event.jaxis.value) <= 20000)){
	  joyx=0;
	}

	if(event.jaxis.axis && (abs(event.jaxis.value) <= 20000)){
	  joyy=0;
	}


	x=joyx;
	y=joyy;

	break;

      case SDL_JOYBUTTONDOWN:  /* Handle Joystick Button Presses */
	if ( event.jbutton.button == 0 )
	  
	    if(playerptr->isAlive()){
	      entityiter=entityptr.end();
	      *entityiter = new GLShot;
	      entityptr.push_back(*entityiter);
	    }else{
	      glLoadIdentity();
	      entityiter=entityptr.end();
	      playerptr->SetDamage(100);
	      *entityiter = playerptr;
	      entityptr.push_back(*entityiter); 
	      playerptr->SetPosition(0, 0, -11);


	      entityiter=entityptr.end();
	      *entityiter = new en_cube(0, 0, -200);
	      entityptr.push_back(*entityiter);
	      (*entityiter)->SetDestroyed(0);

	    } 
	  


	x=joyx;
	y=joyy;

	break;

      case SDL_KEYDOWN:

	if (event.key.state == SDL_PRESSED){

	  switch( event.key.keysym.sym ){

	  case SDLK_LEFT:
	    keyx=-1;
	    break;

	  case SDLK_RIGHT:
	    keyx=1;

	    break;
	  case SDLK_UP:
	    keyy=-1;
	    break;
	  case SDLK_DOWN:
	    keyy=1;
	    break;
	  case SDLK_z:
	    speedup = true;
	    break;
	  case SDLK_x:
	    slowdown = true;
	    break;
	  case SDLK_SPACE:
	    if(playerptr->isAlive()){
	      entityptr.push_back(new GLShot);
 	    }else{
	      glLoadIdentity();
	      entityiter=entityptr.end();
	      playerptr->SetDamage(100);
	      *entityiter = playerptr;
	      entityptr.push_back(*entityiter); 
	      playerptr->SetPosition(0, 0, -11);


	      entityiter=entityptr.end();
	      *entityiter = new en_cube(0, 0, -200);
	      entityptr.push_back(*entityiter);
	      (*entityiter)->SetDestroyed(0);

	    } 
	    break;

	  case SDLK_ESCAPE:
	    return 1;

	  default:
	    break;
	  }
	}	  
	x=keyx;
	y=keyy;

	if((event.key.keysym.sym & SDLK_RETURN) && 
	   (event.key.keysym.mod & (KMOD_ALT | KMOD_META | KMOD_CTRL) )         )
	  {	   
	    return 2; //Send video resize.
	  }

	break;

      case SDL_KEYUP:
	switch(event.key.keysym.sym){
	case SDLK_LEFT:
	  if(keyx==-1){
	    keyx=0;}
	  break;
	case SDLK_RIGHT:
	  if(keyx==1){
	    keyx=0;}
	  break; 
	case SDLK_UP:
	  if(keyy==-1){
	    keyy=0;}
	  break;
	case SDLK_DOWN:
	  if(keyy==1){
	    keyy=0;}
	  break;
	case SDLK_z:
	  speedup = false;
	case SDLK_x:
	  slowdown = false;
	default:
	  break;
	}

	x=keyx;
	y=keyy;

      default:

	break;

      }
    }
  }

  if(playerptr->isAlive()){
    
    if(speedup){
      playerptr->SpeedUp();
    }else if(slowdown){
      playerptr->SlowDown();
    }
    playerptr->move(x,y);
  }else{
    playerptr->move(0,0);
  }

  return 0;

}

