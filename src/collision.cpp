
#include <GL/gl.h>
#include <math.h>
#include <iostream>
#include "collision.h"
#include "BSM.h"
#include "GLEntity.h"
#include "effects.h"

// Here-in lies the collision detection code for bitstream

GLdouble LongestRadius(BSM &bsm){

  GLdouble Rad, LongestRad = 0;
  GLfloat* V;
  V = new GLfloat[3];

  for(int i = 0; i < bsm.GetNumVertices(); i++){
    V = bsm.GetVert(i);
    Rad = sqrt(V[0]*V[0] + V[1]*V[1] + V[2]*V[2]);
    if(Rad > LongestRad){
      LongestRad = Rad;
    }
  }
  cout << LongestRad << endl;
  return LongestRad;

}

bool SphericalHit(GLEntity &object1, GLEntity &object2){

  GLdouble distance, xdist, ydist, zdist, maxradius;
  static position avg;
  int expl_id=0;

  xdist = fabs(object1.getX() - object2.getX());
  ydist = fabs(object1.getY() - object2.getY());
  zdist = fabs(object1.getZ() - object2.getZ());

  distance = sqrt(xdist*xdist + ydist*ydist + zdist*zdist);
  maxradius = object1.GetLongestRadius() + object2.GetLongestRadius();

  if (distance < maxradius){

    if(expl_id == 0){
      //     cout << "Spherical Collision Detected" << endl;
      avg.x = (object1.getX() + object2.getX())/2;
      avg.y = (object1.getY() + object2.getY())/2;
      avg.z = (object1.getZ() + object2.getZ())/2;
      explosion(avg, 0.5, 0.5, expl_id);
      return true;
    }
    
  }



  return false;
}
