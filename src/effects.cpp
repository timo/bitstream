

#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include "physics.h"
#include "effects.h"
#include <vector>

#define EXPLOSIONS 20
#define PARTICLE_EXPLOSIONS 20
#define PARTICLES 100

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
  for(int i = 1; i < PARTICLE_EXPLOSIONS; i++){
    particle_explosion(dummy, 0, 0, i);
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
      //      cout << "Explosion # " << i << endl;

  }

  if(explosionindex[index]==0){
    return -1;
  }



  alpha[index] = 1.0 - (double)(SDL_GetTicks() - starttime[index]) /(e_duration[index]*1000);
  //cout << alpha[index] << endl;

  if((alpha[index] < 0.01) && (explosionindex[index] == 1)){

    explosionindex[index]=0;
    alpha[index] = 1.0;
    gluDeleteQuadric(qobj[index]);
    qobj[index] = NULL;
    //   cout << "Deleting Explosion #" << index << endl;
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


// Particle explosion

int particle_explosion(const position &source, const double& speed, const double &duration, int &index){

  static int explosionindex[PARTICLE_EXPLOSIONS];
  static Uint32 starttime[PARTICLE_EXPLOSIONS];
  static int firstrun = 1;
  static position e_pos[PARTICLE_EXPLOSIONS][PARTICLES];
  static velocity e_vel[PARTICLE_EXPLOSIONS][PARTICLES];
  static acceleration e_acc[PARTICLE_EXPLOSIONS][PARTICLES];
  static const double GRAVITY = -9.81;
  static Uint32 lasttime[PARTICLE_EXPLOSIONS];
  static double e_speed[PARTICLE_EXPLOSIONS];
  static double e_duration[PARTICLE_EXPLOSIONS];
  static double alpha[PARTICLE_EXPLOSIONS];
  Uint32 deltatime;
  int i;

  if(firstrun == 1){
    for(i=0; i < PARTICLE_EXPLOSIONS; i++){
      explosionindex[i] = 0;
    }
      firstrun=0;
  }

  if( index == 0 ){    
      i=1;
      while(explosionindex[i] == 1){
	i++;
	if(i == PARTICLE_EXPLOSIONS-1) {
	  return -1;  // Couldn't find a spot
	}
      }
      explosionindex[i]=1;
      //   cout << "Creating Particle Explosion #" << i << endl;
      index = i;
      lasttime[i] = SDL_GetTicks();
      for(int j = 0; j < PARTICLES; j++){
	e_speed[i] = speed;
	e_duration[i] = duration;
	starttime[i] = lasttime[i];
	e_pos[i][j] = source;
	e_pos[i][j].boundaries = 0;
	e_vel[i][j].x = rand()%(int)speed;
	e_vel[i][j].y = rand()%(int)speed;
	e_vel[i][j].z = rand()%(int)speed;
	if(rand()%2) e_vel[i][j].x *=-1;
	if(rand()%2) e_vel[i][j].y *=-1;
	if(rand()%2) e_vel[i][j].z *=-1;
	e_acc[i][j].x = rand()%5;
	if(rand()%2) e_acc[i][j].x *=-1;
	e_acc[i][j].y = GRAVITY;
	e_acc[i][j].z = rand()%5;
	if(rand()%2) e_acc[i][j].z *=-1;
      }
  }
      
  if(explosionindex[index]==0){
    return -1;
  }

  i = index;

  //  cout << "Preparing to draw explosion #" << i << endl;

  deltatime = SDL_GetTicks() - lasttime[i];
  lasttime[i] = SDL_GetTicks();

  alpha[index] = 1.0 - (double)(lasttime[index] - starttime[index]) /(e_duration[index]*1000);

  if((alpha[index] < 0.01) && (explosionindex[index] == 1)){

    explosionindex[index]=0;
    alpha[index] = 1.0;
    return 0;

  }

  glEnable(GL_TEXTURE_2D);
  glBindTexture( GL_TEXTURE_2D, spark.getID() );
  glBlendFunc(GL_SRC_ALPHA , GL_ONE);
  glDisable( GL_LIGHTING );
  glDisable( GL_DEPTH_TEST );

  for(int j = 0; j < PARTICLES; j++){
    UpdateVelocity(e_vel[i][j], e_acc[i][j], (double)deltatime/1000);
    UpdatePosition(e_pos[i][j], e_vel[i][j], (double)deltatime/1000);
    
    // Actually draw the particle
    //    cout << "Drawing Particle #" << j << endl;
    glPushMatrix();
    glTranslatef(e_pos[i][j].x, e_pos[i][j].y, e_pos[i][j].z);
    //  glColor4f(1.0/((double)(rand()%10)), 1.0/((double)(rand()%10)), 1.0/((double)(rand()%10)),  alpha[index]);
    glColor4f(1.0, 1.0, 1.0, alpha[index]);
    glBegin(GL_QUADS);
    glLoadIdentity();
    glTexCoord2d(0, 0); 
    glVertex3f(0.0, 0.0, 0.0);
    glTexCoord2d(0, 1); 
    glVertex3f(0.0, 1.0, 0.0);
    glTexCoord2d(1, 1); 
    glVertex3f(1.0, 1.0, 0.0);
    glTexCoord2d(1, 0); 
    glVertex3f(1.0, 0.0, 0.0);
    
    glEnd();
    glPopMatrix();
  }
  
  glBlendFunc(GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA);
  glEnable( GL_LIGHTING );
  glEnable( GL_DEPTH_TEST );
  glDisable(GL_TEXTURE_2D);

  // cout << "Exiting Particle Explosion" << endl;
  return 0;
}
