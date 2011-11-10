
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

  for(int i = 0; i < bsm.GetNumVertices(); i+=3) {
    V[0] = bsm.GetVert(i+0);
    V[1] = bsm.GetVert(i+1);
    V[2] = bsm.GetVert(i+2);
    Rad = sqrt(V[0]*V[0] + V[1]*V[1] + V[2]*V[2]);
    if(Rad > LongestRad){
      LongestRad = Rad;
    }
  }

  delete[] V;


#ifdef VERBOSE
  cout << LongestRad << endl;
#endif
  return LongestRad;
}

bool SphericalHit(GLEntity &object1, GLEntity &object2){

  GLdouble distance, xdist, ydist, zdist, maxradius;


  xdist = fabs(object1.getX() - object2.getX());
  ydist = fabs(object1.getY() - object2.getY());
  zdist = fabs(object1.getZ() - object2.getZ());

  distance = sqrt(xdist*xdist + ydist*ydist + zdist*zdist);
  maxradius = object1.GetLongestRadius() + object2.GetLongestRadius();

  if (distance < maxradius){

      return true;
    
  }



  return false;
}
