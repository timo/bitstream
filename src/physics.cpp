#include "physics.h"
//

//Simeple constant acceleration physics

void UpdateVelocity(velocity &v, const acceleration &a, const double &deltatime){

  v.x += a.x*deltatime;
  v.y += a.y*deltatime;
  v.z += a.z*deltatime;

} 

void UpdatePosition(position &p, const velocity& v, const double &deltatime){

  p.x += v.x*deltatime;
  p.y += v.y*deltatime;
  p.z += v.z*deltatime;


  if(p.boundaries){
    if(p.x > X_RIGHT_BOUND){
      p.x = X_RIGHT_BOUND;
    }
    else if(p.x < X_LEFT_BOUND){
      p.x = X_LEFT_BOUND;
    }
    
    if(p.y > Y_TOP_BOUND){
      p.y = Y_TOP_BOUND;
    }
    else if(p.y < Y_BOTTOM_BOUND){
      p.y = Y_BOTTOM_BOUND;
    }

    if(p.z > Z_FRONT_BOUND){
      p.z = Z_FRONT_BOUND;
    }
    else if(p.z < Z_BACK_BOUND){
      p.z = Z_BACK_BOUND;
    }
  }
}
 
