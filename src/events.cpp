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
#include <vector>
#include <deque>
#include <list>
#include "GLEntity.h"
#include "GLPlayer.h"
#include "GLMap.h"
#include "GLShot.h"
	

using namespace std;

extern list < GLEntity * > entityptr;
extern list <GLEntity * >::iterator entityiter;
extern unsigned entitysize;


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
	return 0;

      case SDL_QUIT:
	return 1;

      case SDL_JOYAXISMOTION:

	if(event.jaxis.axis && event.jaxis.value < 0){
	  joyy=-1;   
	}

        if(event.jaxis.axis && event.jaxis.value > 0){
	  joyy=1;
	}

	if(!event.jaxis.axis  && event.jaxis.value > 0){
	  joyx=1;

	}

	if(!event.jaxis.axis && event.jaxis.value < 0){
	  joyx=-1;
	}

	if(!event.jaxis.axis && !event.jaxis.value){
	  joyx=0;
	}

	if(event.jaxis.axis && !event.jaxis.value){
	  joyy=0;
	}

	if(event.jaxis.axis && !event.jaxis.value){
	  joyy=0;
	}

	x=joyx;
	y=joyy;

	break;

      case SDL_JOYBUTTONDOWN:  /* Handle Joystick Button Presses */
	if ( event.jbutton.button == 0 )
	  {
	    if(Player1.isAlive()){
	      entityiter=entityptr.end();
	      *entityiter = new GLShot;
	      entityptr.push_back(*entityiter);
	    }
	  }

	x=joyx;
	y=joyy;

	break;

      case SDL_KEYDOWN:

	cout << SDL_GetKeyName(event.key.keysym.sym) << endl;
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
	  case SDLK_SPACE:
	    if(Player1.isAlive()){
	      entityiter=entityptr.end();
	      *entityiter = new GLShot;
	      entityptr.push_back(*entityiter);
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

	if((event.key.keysym.sym  & SDLK_RETURN) && 
	   (event.key.keysym.mod & (KMOD_ALT | KMOD_META | KMOD_CTRL) )         )
	  {	   
	    return 2; //Send video resize data.
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

  /* Check current key state for special commands */

  if(Player1.isAlive()){
    
    Player1.move(x,y);

  }
  return 0;

}

//Based of ryan gordon's code in ROTT
int attempt_fullscreen_toggle(SDL_Surface **surface, Uint32 *flags)
{
    long framesize = 0;
    void *pixels = NULL;
    SDL_Rect clip;
    Uint32 tmpflags = 0;
    int w = 0;
    int h = 0;
    int bpp = 0;
    int grabmouse = (SDL_WM_GrabInput(SDL_GRAB_QUERY) == SDL_GRAB_ON);
    int showmouse = SDL_ShowCursor(-1);
    SDL_Color *palette = NULL;
    int ncolors = 0;

    /*
    sdldebug("attempting to toggle fullscreen flag...");
    */

    if ( (!surface) || (!(*surface)) )  /* don't try if there's no surface. */
    {
	    /*
        sdldebug("Null surface (?!). Not toggling fullscreen flag.");
	*/
        return(0);
    } /* if */

       if (SDL_WM_ToggleFullScreen(*surface))
        {
	    /*
        sdldebug("SDL_WM_ToggleFullScreen() seems to work on this system.");
	*/
          if (flags)
               *flags ^= SDL_FULLSCREEN;
          return(1);
	} /* if */

    if ( !(SDL_GetVideoInfo()->wm_available) )
    {
	    /*
        sdldebug("No window manager. Not toggling fullscreen flag.");
	*/
        return(0);
    } /* if */

    /*
    sdldebug("toggling fullscreen flag The Hard Way...");
    */
    tmpflags = (*surface)->flags;
    w = (*surface)->w;
    h = (*surface)->h;
    bpp = (*surface)->format->BitsPerPixel;
    
    if (flags == NULL)  /* use the surface's flags. */
        flags = &tmpflags;

    SDL_GetClipRect(*surface, &clip);

        /* save the contents of the screen. */
    if ( (!(tmpflags & SDL_OPENGL)) && (!(tmpflags & SDL_OPENGLBLIT)) )
    {
        framesize = (w * h) * ((*surface)->format->BytesPerPixel);
	pixels = new void*[framesize];
	//      pixels = malloc(framesize);
        if (pixels == NULL)
            return(0);
        memcpy(pixels, (*surface)->pixels, framesize);
    } /* if */

    if (grabmouse)
        SDL_WM_GrabInput(SDL_GRAB_OFF);

    SDL_ShowCursor(1);

    *surface = SDL_SetVideoMode(w, h, bpp, (*flags) ^ SDL_FULLSCREEN);

    if (*surface != NULL)
        *flags ^= SDL_FULLSCREEN;

    else  /* yikes! Try to put it back as it was... */
    {
        *surface = SDL_SetVideoMode(w, h, bpp, tmpflags);
        if (*surface == NULL)  /* completely screwed. */
        {
            if (pixels != NULL)
                free(pixels);
            if (palette != NULL)
                free(palette);
            return(0);
        } /* if */
    } /* if */

    /* Unfortunately, you lose your OpenGL image until the next frame... */

    if (pixels != NULL)
    {
        memcpy((*surface)->pixels, pixels, framesize);
        free(pixels);
    } /* if */

#if 1
    //    STUB_FUNCTION;   /* palette is broken. FIXME !!! --ryan. */
#else
    if (palette != NULL)
    {
            /* !!! FIXME : No idea if that flags param is right. */
        SDL_SetPalette(*surface, SDL_LOGPAL, palette, 0, ncolors);
        free(palette);
    } /* if */
#endif

    SDL_SetClipRect(*surface, &clip);

    if (grabmouse)
        SDL_WM_GrabInput(SDL_GRAB_ON);

    SDL_ShowCursor(showmouse);

#if 0
    STUB_FUNCTION;  /* pull this out of buildengine/sdl_driver.c ... */
    output_surface_info(*surface);
#endif

    return(1);
} /* attempt_fullscreen_toggle */
