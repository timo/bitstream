//////////////////////////////////////////////////////////////////////////
// Name: en_turret 
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
#include "en_turret.h"                                // class implemented
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


en_turret::en_turret(const double&x, const double&y, const double&z)
  :GLEnemy(x,y,z)
{
  m_Position.x=x;
  m_Position.y=y;
  m_Position.z=z;
  build();

}// en_turret
en_turret::en_turret(const position& pos)
  :GLEnemy(pos)
{
  m_Position=pos;
  build();

}// en_turret


void 
en_turret::build(){

  m_LastTime=0;
  m_model.LoadBSM("data/enemies/turret/turret.bsm");
  m_model.SetMainDamage(MAX_HEALTH);
  m_IdleTime = 0;
  m_Position.boundaries = 0;
  m_dDamage = 20;
  m_Behavior = IDLE;
  m_Color[RED]=0.5;
  m_Color[GREEN]=0;
  m_Color[BLUE]=1;
  m_Color[ALPHA]=1;
  m_Velocity.x = 0;
  m_Velocity.y = 0;
  m_Velocity.z = playerptr->GetVelocity();
  m_Acceleration.x = 0;
  m_Acceleration.y = 0;
  m_Acceleration.z = 0;

}


en_turret::en_turret(const en_turret&)
{
}// en_turret

en_turret::~en_turret()
{
  int index=0;

  particle_explosion(m_Position, 5, 1, index);

}// ~en_turret


//============================= Operators ====================================

en_turret& 
en_turret::operator=(const en_turret&rhs)
{
   if ( this==&rhs ) {
        return *this;
    }
    //superclass::operator =(rhs);

    //add local assignments

    return *this;

}// =

void
en_turret::en_attack_state()
{

  static double accum = 0;
  accum += m_DeltaSeconds;

  m_Acceleration.z = 0;
  m_Velocity.z = playerptr->GetVelocity();


  if(accum > 1){

    entityiter=entityptr.end();
    *entityiter = new en_weapon(m_Position.x, m_Position.y, m_Position.z + 5);
    entityptr.push_back(*entityiter);
    accum = 0;
  }
  

  if(m_Position.z > 10){
    m_model.hit(100);
  }

  UpdateVelocity(m_Velocity, m_Acceleration, m_DeltaSeconds);
  UpdatePosition(m_Position, m_Velocity, m_DeltaSeconds);
}

void
en_turret::en_react_state()
{
  
  m_Behavior = ATTACK;

}
     
void 
en_turret::en_idle_state()
{
  

  m_IdleTime += m_DeltaSeconds;
  m_Velocity.z = playerptr->GetVelocity();
  //  cout << m_Position.z << endl;

  UpdateVelocity(m_Velocity, m_Acceleration, m_DeltaSeconds);
  UpdatePosition(m_Position, m_Velocity, m_DeltaSeconds);


}

void 
en_turret::en_move()
{

  if(!m_LastTime){ 
    m_LastTime= SDL_GetTicks();
    m_Acceleration.x = 0;
    m_Acceleration.y = 0;
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
en_turret::draw()
{
  this->en_move();

  glPushMatrix();

  glTranslatef(m_Position.x, m_Position.y, m_Position.z);

  glRotatef(45, 0, 1, 1);
 
  glColor4fv(m_Color);

  m_model.draw();

  glPopMatrix();
}

GLdouble 
en_turret::GetLongestRadius(){

  return  m_model.GetLongestRadius();

 
}

GLdouble 
en_turret::getX(){

  return m_Position.x;

}

GLdouble 
en_turret::getY(){

  return m_Position.y;

}

GLdouble 
en_turret::getZ(){

  return m_Position.z;
  
}



void 
en_turret::ApplyDamage(const GLdouble &hit){
  
  m_model.hit(hit);
}

GLdouble 
en_turret::GetHitDamage(){

  return m_dDamage;
}

bool 
en_turret::isAlive(){

  if(m_model.getDamage()<=0) return false;

  return true;
  
}
//============================= Operations ===================================
//============================= Access      ==================================
//============================= Inquiry    ===================================
/////////////////////////////// Protected Methods ////////////////////////////

/////////////////////////////// Private   Methods ////////////////////////////
