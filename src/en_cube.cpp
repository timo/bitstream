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

/////////////////////////////// Public ///////////////////////////////////////

//============================= Lifecycle ====================================

en_cube::en_cube(const GLdouble &x, const GLdouble&y, const GLdouble&z)
  :GLEnemy(x, y, z)
{

  m_model.LoadBSM("data/enemies/cube/cube.bsm");

}// en_cube

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

}

void 
en_cube::en_move()
{

}


void 
en_cube::draw()
{

  if(!m_dLasttime){ m_dLasttime= SDL_GetTicks();}

  GLdouble deltatime = (double)(SDL_GetTicks() - m_dLasttime)/8.0;

  m_dLasttime = SDL_GetTicks();

  m_zTilt += deltatime;

  glPushMatrix();

  glTranslatef(this->getX(),this->getY(),this->getZ());
  glRotatef(m_zTilt, 0, 1, 1);

  glColor4f(0.0, 0.8, 0.0, 0.5);
  m_model.draw();

  glPopMatrix();
}



//============================= Operations ===================================
//============================= Access      ==================================
//============================= Inquiry    ===================================
/////////////////////////////// Protected Methods ////////////////////////////

/////////////////////////////// Private   Methods ////////////////////////////
