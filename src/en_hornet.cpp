//////////////////////////////////////////////////////////////////////////
// Name: en_hornet 
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
#include <list>
#include "en_hornet.h"                                // class implemented
#include "GLEntity.h"
#include "GLPlayer.h"
#include "GLShot.h"
#include "physics.h"
#include "effects.h"
#include "en_attack.h"
/////////////////////////////// Public ///////////////////////////////////////
using namespace std;
//============================= Lifecycle ====================================
const int ROT_PER_SEC = 90;
const double MSEC_PER_SEC = 1000;
const double REACTION_TIME = 5;
const double MAX_HEALTH = 30;

extern GLPlayer* playerptr;
extern list < GLEntity * > entityptr;
extern list <GLEntity * >::iterator entityiter;


en_hornet::en_hornet(const double&x, const double&y, const double&z)
  :GLEnemy(x,y,z)
{
  m_Position.x=x;
  m_Position.y=y;
  m_Position.z=z;
  build();

}// en_hornet
en_hornet::en_hornet(const position& pos)
  :GLEnemy(pos)
{
  m_Position=pos;
  build();

}// en_hornet


void 
en_hornet::build(){

  m_LastTime=0;
  // m_model.LoadBSM("data/enemies/hornet/hornet.bsm");
  m_model.LoadBSM("data/enemies/hornet/hornet.bsm");
  m_model.SetMainDamage(MAX_HEALTH);
  m_IdleTime = 0;
  m_Position.boundaries = 1;
  m_dDamage = 20;
  m_Behavior = IDLE;
  m_Color[RED]=0.5;
  m_Color[GREEN]=0.5;
  m_Color[BLUE]=0;
  m_Color[ALPHA]=1;
  m_Velocity.x = 0;
  m_Velocity.y = 0;
  m_Velocity.z = playerptr->GetVelocity();
  m_Acceleration.x = 0;
  m_Acceleration.y = 0;
  m_Acceleration.z = 0;

}


en_hornet::en_hornet(const en_hornet&)
{
}// en_hornet

en_hornet::~en_hornet()
{
  int index=0;

  particle_explosion(m_Position, 5, 1, index);

}// ~en_hornet


//============================= Operators ====================================

en_hornet& 
en_hornet::operator=(const en_hornet&rhs)
{
   if ( this==&rhs ) {
        return *this;
    }
    //superclass::operator =(rhs);

    //add local assignments

    return *this;

}// =

void
en_hornet::en_attack_state()
{

  static double accum = 0;
  m_Rotation.z += m_DeltaSeconds*ROT_PER_SEC;  
  accum += m_DeltaSeconds;

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
  m_Velocity.z = 0;


  if(accum > 1){

    entityiter=entityptr.end();
    *entityiter = new en_weapon(m_Position.x, m_Position.y, m_Position.z + 5);
    entityptr.push_back(*entityiter);
    accum = 0;
  }
  

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
en_hornet::en_react_state()
{
  
  m_Rotation.z += m_DeltaSeconds*ROT_PER_SEC;
  m_Behavior = ATTACK;

}
     
void 
en_hornet::en_idle_state()
{
  

  m_Rotation.z += m_DeltaSeconds*ROT_PER_SEC;
  m_IdleTime += m_DeltaSeconds;

  m_Velocity.z = playerptr->GetVelocity();
  if(m_IdleTime > rand()%2){
    srand(SDL_GetTicks());
    m_IdleTime = -(rand()%2);
    m_Acceleration.x *= -1;
    m_Acceleration.y *= -1;

  }

  //  cout << m_Position.z << endl;

  if(m_Position.z > m_dDepth){
    m_dDepth -=5;
    m_Behavior = REACT;
    if(m_dDepth < -50) m_dDepth = -30;
  }

  UpdateVelocity(m_Velocity, m_Acceleration, m_DeltaSeconds);
  UpdatePosition(m_Position, m_Velocity, m_DeltaSeconds);


}

void 
en_hornet::en_move()
{

  if(!m_LastTime){ 
    m_LastTime= SDL_GetTicks();
    m_Acceleration.x = 4;
    m_Acceleration.y = 2;
    m_Acceleration.z = 0; 

  }

  m_DeltaSeconds = (double)(SDL_GetTicks() - m_LastTime)/MSEC_PER_SEC;
  m_LastTime = SDL_GetTicks();

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
en_hornet::draw()
{
  this->en_move();

  glPushMatrix();

  glTranslatef(m_Position.x, m_Position.y, m_Position.z);

  glRotatef(m_Rotation.z, 0, 0, 1);

  glColor4fv(m_Color);

  m_model.draw();

  glPopMatrix();
}

GLdouble 
en_hornet::GetLongestRadius(){

  return  m_model.GetLongestRadius();

 
}

GLdouble 
en_hornet::getX(){

  return m_Position.x;

}

GLdouble 
en_hornet::getY(){

  return m_Position.y;

}

GLdouble 
en_hornet::getZ(){

  return m_Position.z;
  
}



void 
en_hornet::ApplyDamage(const GLdouble &hit){
  
  m_model.hit(hit);
}

GLdouble 
en_hornet::GetHitDamage(){

  return m_dDamage;
}


bool 
en_hornet::isAlive(){

  if(m_model.getDamage()<=0) return false;

  return true;
  
}
GLdouble
en_hornet::m_dDepth = -30;
//============================= Operations ===================================
//============================= Access      ==================================
//============================= Inquiry    ===================================
/////////////////////////////// Protected Methods ////////////////////////////

/////////////////////////////// Private   Methods ////////////////////////////
