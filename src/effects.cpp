

#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include "physics.h"
#include "effects.h"
#include <vector>

#define EXPLOSIONS 120

using namespace std;

int explosion(const position&pos, const double &radius, const double&duration, int&index);

void process_effects(){

  position dummy;
  dummy.x=0;
  dummy.y=0;
  dummy.z=0;

  for(int i = 1; i < EXPLOSIONS; i++){
    explosion(dummy, 0, 0, i);
  }

}


int explosion(const position&pos, const double &radius, const double&duration, int&index){

  static int explosionindex[EXPLOSIONS];
  static Uint32 starttime[EXPLOSIONS];

  static GLfloat alpha[EXPLOSIONS];
  static int firstrun = 1;
  static GLUquadricObj* qobj[EXPLOSIONS];

  static position e_pos[EXPLOSIONS];
  static double e_radius[EXPLOSIONS];
  static double e_duration[EXPLOSIONS];
  int i;

  if(index==999){
    return 0;
  }

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
      e_pos[i] = pos;
      e_radius[i] = radius;
      e_duration[i] = duration;
      index = i;
      cout << "Explosion # " << i << endl;

  }

  if(explosionindex[index]==0){
    return 0;
  }



  alpha[index] = 1.0 - (double)(SDL_GetTicks() - starttime[index]) /(e_duration[index]*1000);
  //cout << alpha[index] << endl;

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
    gluQuadricOrientation(qobj[index], GLU_OUTSIDE);
    gluQuadricDrawStyle(qobj[index], GLU_FILL);
    gluQuadricNormals(qobj[index], GLU_SMOOTH); 
    
    glTranslatef(e_pos[index].x, e_pos[index].y, e_pos[index].z);
    glColor4f(1.0f, 0.5f, 0.0f, alpha[index]);
    
    gluSphere(qobj[index], e_radius[index], 15, 15);

    glPopMatrix(); 
    
  }

  return index;

}

