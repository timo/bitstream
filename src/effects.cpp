
#ifndef _effects_h_
#define _effects_h_

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include "physics.h"
#include <vector>

#define EXPLOSIONS 20

using namespace std;

int explosion(const position&pos, const double &radius, const double&duration, int&index){

  if(index==999){
    return 0;
  }

  static int explosionindex[EXPLOSIONS];
  static Uint32 starttime[EXPLOSIONS];

  static GLfloat alpha[EXPLOSIONS];
  static int firstrun = 1;
  static GLUquadricObj* qobj[EXPLOSIONS];
  int i;

  if(firstrun == 1){
    for(i=0; i < EXPLOSIONS; i++){
      explosionindex[i] = 0;
      alpha[i]=1.0;
      qobj[index] = NULL;
    }
      firstrun=0;
  }

  // cout << "Index #" << index << endl;
  if( index == 0 ){    
      i=1;
;
      while(explosionindex[i] == 1){
	i++;
	if(i == EXPLOSIONS-1) {
	  //	  cout << "Too many explosions" << endl;
	  return 0;  // Couldn't find a spot
	}
      }
      explosionindex[i]=1;
      starttime[i] = SDL_GetTicks();
 
      index = i;
      //    cout << "Explosion # " << i << endl;

  }




  alpha[index] = 1.0 - (double)(SDL_GetTicks() - starttime[index]) /(duration*1000);


  if((alpha[index] < 0.0) && (explosionindex[index] == 1)){

    explosionindex[index]=0;
    alpha[index] = 1.0;
    gluDeleteQuadric(qobj[index]);
    qobj[index] = NULL;
    cout << "Deleting #" << index << endl;
    index = 999;

    return 0 ;
  }
  else{

    glPushMatrix();

    if(qobj[index]){
      gluDeleteQuadric(qobj[index]);
    }
    qobj[index] = gluNewQuadric();
    gluQuadricOrientation(qobj[index], GLU_INSIDE);
    gluQuadricDrawStyle(qobj[index], GLU_FILL);
    gluQuadricNormals(qobj[index], GLU_FLAT); 
    
    glTranslatef(pos.x, pos.y, pos.z);
    glColor4f(1.0f, 0.5f, 0.0f, alpha[index]);
    
    gluSphere(qobj[index], radius, 15, 10);
    
    glPopMatrix(); 
    
  }

  return index;

}

#endif // _effects_h_
