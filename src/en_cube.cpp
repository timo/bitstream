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
#include "en_cube.h"                                // class implemented
#include "GLEntity.h"
#include "physics.h"
/////////////////////////////// Public ///////////////////////////////////////

//============================= Lifecycle ====================================
const int ROT_PER_SEC = 90;
const double MSEC_PER_SEC = 1000;


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
  m_IdleTime = 0;
  m_Position.boundaries = 1;
}


en_cube::en_cube(const en_cube&)
{
}// en_cube

en_cube::~en_cube()
{
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
en_cube::en_attack()
{

}
   
void 
en_cube::en_idle()
{
  
  if(!m_LastTime){ 
    m_LastTime= SDL_GetTicks();
    m_Acceleration.x = 4;
    m_Acceleration.y = 2;
    m_Acceleration.z = 2;
  }

  GLdouble deltatime = (double)(SDL_GetTicks() - m_LastTime)/MSEC_PER_SEC;

  srand(SDL_GetTicks());

  m_LastTime = SDL_GetTicks();

  m_Rotation.z += deltatime*ROT_PER_SEC;
  m_IdleTime += deltatime;

  if(m_IdleTime > rand()%2){
    srand(SDL_GetTicks());
    m_IdleTime = -(rand()%2);
    m_Acceleration.x *= -1;
    m_Acceleration.y *= -1;
    m_Acceleration.z *= -1;
  }

  UpdateVelocity(m_Velocity, m_Acceleration, deltatime);
  UpdatePosition(m_Position, m_Velocity, deltatime);


}

void 
en_cube::en_move()
{

}



void 
en_cube::draw()
{
  this->en_idle();

  glPushMatrix();

  glTranslatef(m_Position.x, m_Position.y, m_Position.z);

  glRotatef(m_Rotation.z, 0, 1, 1);

  glColor4f(0.0, 0.8, 0.0, 0.5);
  m_model.draw();

  glPopMatrix();
}



//============================= Operations ===================================
//============================= Access      ==================================
//============================= Inquiry    ===================================
/////////////////////////////// Protected Methods ////////////////////////////

/////////////////////////////// Private   Methods ////////////////////////////
