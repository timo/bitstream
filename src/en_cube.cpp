//////////////////////////////////////////////////////////////////////////
// Name: en_cube 
//
// Files:
// Bugs:
// See Also:
// Type: C++-Source
//////////////////////////////////////////////////////////////////////////
// Authors:
// Date:
//////////////////////////////////////////////////////////////////////////
// Modifications:
//
/////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "en_cube.h"                                // class implemented
#include "GLEntity.h"
#include "GLPlayer.h"
#include "physics.h"
#include "effects.h"
/////////////////////////////// Public ///////////////////////////////////////
using namespace std;
//============================= Lifecycle ====================================
const int ROT_PER_SEC = 90;
const double MSEC_PER_SEC = 1000;
const double REACTION_TIME = 5;
const double MAX_HEALTH = 30;
extern GLPlayer* playerptr;

en_cube::en_cube(const double &x, const double &y, const double &z)
  :GLEnemy(x,y,z)
{
  m_Position.x=x;
  m_Position.y=y;
  m_Position.z=z;
  build();

}// en_cube
en_cube::en_cube(const position& pos)
  :GLEnemy(pos)
{
  m_Position=pos;
  build();

}// en_cube


void 
en_cube::build(){

  m_LastTime=0;
  m_model.LoadBSM("data/enemies/cube/cube.bsm");
  m_model.SetMainDamage(MAX_HEALTH);
  m_IdleTime = 0;
  m_Position.boundaries = 1;
  m_dDamage = 20;
  m_Behavior = IDLE;
  m_Color[RED]=0;
  m_Color[GREEN]=1;
  m_Color[BLUE]=0;
  m_Color[ALPHA]=1;
  m_Velocity.x = 0;
  m_Velocity.y = 0;
  m_Velocity.z = playerptr->GetVelocity();
  m_Acceleration.x = 0;
  m_Acceleration.y = 0;
  m_Acceleration.z = 0;
}

// GLint en_cube::m_iDestroyed=0;

en_cube::en_cube(const en_cube&)
{
}// en_cube

en_cube::~en_cube()
{
  int index=0;
  //  explosion(m_Position, 2, 1, index);
  index=0;
  particle_explosion(m_Position, 5, 1, index);
  //  cout << "Destroying a cube" << endl;
}// ~en_cube


//============================= Operators ====================================

en_cube& 
en_cube::operator=(const en_cube&rhs)
{
   if ( this==&rhs ) {
        return *this;
    }
    //superclass::operator =(rhs);

    //add local assignments

    return *this;

}// =

void
en_cube::en_attack_state()
{
  m_Rotation.z += m_DeltaSeconds*ROT_PER_SEC;  

  if(playerptr->getX() > m_Position.x){
    m_Acceleration.x = 5*(playerptr->getX()-m_Position.x) - m_Velocity.x;
  }else{
    m_Acceleration.x = -5*(-playerptr->getX()+m_Position.x) + m_Velocity.x;
  }
  //  cout << m_Velocity.z << endl;
  if(playerptr->getY() > m_Position.y){
    m_Acceleration.y = 5*(playerptr->getY()-m_Position.y) - m_Velocity.y;
  }else{
    m_Acceleration.y = -5*(-playerptr->getY()+m_Position.y) + m_Velocity.y;
  }

  m_Acceleration.z = 0;

 
  if(m_Position.z > 10){
    m_model.hit(100);
  }

  if(m_Position.y < -5 + m_model.GetLongestRadius()){
    m_Velocity.y = 10;
  }
  UpdateVelocity(m_Velocity, m_Acceleration, m_DeltaSeconds);
  UpdatePosition(m_Position, m_Velocity, m_DeltaSeconds);
}

void
en_cube::en_react_state()
{
  
  m_Rotation.z += m_DeltaSeconds*ROT_PER_SEC;

  if(m_Color[RED] < 1){ m_Color[RED] += m_DeltaSeconds; }
  else{ m_Color[RED] = 1; }
  if(m_Color[GREEN] > 0){ m_Color[GREEN] -= m_DeltaSeconds; }
  else{ 
    m_Color[GREEN] = 0; 
    m_Behavior = ATTACK;
    m_Position.boundaries = 0;
    m_Velocity.x = 0;
    m_Velocity.y = 0;
    
  }
}
     
void 
en_cube::en_idle_state()
{
  

  m_Rotation.z += m_DeltaSeconds*ROT_PER_SEC;
  m_IdleTime += m_DeltaSeconds;

  if(m_IdleTime > rand()%2){
    srand(SDL_GetTicks());
    m_IdleTime = -(rand()%2);
    m_Acceleration.x *= -1;
    m_Acceleration.y *= -1;
    //    m_Acceleration.z *= -1;
  }

  //  cout << m_Position.z << endl;

  if(m_Position.z > -70){
    m_Behavior = REACT;
  }
  if(m_Position.z > 10){
    m_model.hit(100);
  }

  UpdateVelocity(m_Velocity, m_Acceleration, m_DeltaSeconds);
  UpdatePosition(m_Position, m_Velocity, m_DeltaSeconds);


}

void 
en_cube::en_move()
{

  if(!m_LastTime){ 
    m_LastTime= SDL_GetTicks();
    m_Acceleration.x = 4;
    m_Acceleration.y = 2;
    m_Acceleration.z = 0;
  }

  if(m_Behavior == IDLE){
    if(m_model.getDamage() < MAX_HEALTH){ m_Behavior = REACT; }
  }

  m_DeltaSeconds = (double)(SDL_GetTicks() - m_LastTime)/MSEC_PER_SEC;
  m_LastTime = SDL_GetTicks();

  m_Velocity.z = playerptr->GetVelocity();
  switch(m_Behavior){
  case IDLE:
    this->en_idle_state();
    break;
  case REACT:
    this->en_react_state();
    break;
  case ATTACK:
    this->en_attack_state();
    break;
  default:
    break;
  }


}



void 
en_cube::draw()
{
  this->en_move();
  
  glPushMatrix();
  glMatrixMode(GL_MODELVIEW);
  glTranslatef(m_Position.x, m_Position.y, m_Position.z);

  glRotatef(m_Rotation.z, 0, 1, 1);

  glColor4fv(m_Color);

  m_model.draw();

  glPopMatrix();
}

GLdouble 
en_cube::GetLongestRadius(){

  return  m_model.GetLongestRadius();

}

GLdouble 
en_cube::getX(){

  return m_Position.x;

}

GLdouble 
en_cube::getY(){

  return m_Position.y;

}

GLdouble 
en_cube::getZ(){

  return m_Position.z;
  
}



void 
en_cube::ApplyDamage(const GLdouble &hit){
  
  m_model.hit(hit);
  
}

GLdouble 
en_cube::GetHitDamage(){

  return m_dDamage;
}


bool 
en_cube::isAlive(){

  if(m_model.getDamage()<=0) return false;

  return true;
  
}
//============================= Operations ===================================
//============================= Access      ==================================
//============================= Inquiry    ===================================
/////////////////////////////// Protected Methods ////////////////////////////

/////////////////////////////// Private   Methods ////////////////////////////
