/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: t; c-basic-offset: 3 -*- */
///////////////////////////////////////////////////////////////////////////
// Name: en_cube 
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
// Modifications:
//
//
///////////////////////////////////////////////////////////////////////////
#ifndef _en_cube_h_
#define _en_cube_h_

// System Includes
//

// Project Includes
//

#include "BSM.h"
#include "GLEnemy.h"
#include "physics.h"

// Local Includes
//

// Forward References
//

/**   
  *    @author 
  *    @date 
  */
class en_cube : public GLEnemy
{
public:

// Lifecycle
   en_cube(const double &x=0, const double &y=0, const double &z=0);
   en_cube(const position &);
   en_cube(const en_cube&);            // copy constructor
   ~en_cube();

// Operator
   
   en_cube&   operator=(const en_cube&);     // assignment operator

// Operations
	void build();  // Common constructor code
	void en_attack();
   void en_idle();
	void en_move();
   void draw();
   GLdouble GetLongestRadius();
// Access

	GLdouble getX();
	GLdouble getY();
	GLdouble getZ();

protected:
// Protected Methods
private:
// Private Methods
	BSM m_model;
   velocity m_Velocity;
   acceleration m_Acceleration;
   position m_Position;
   rotation m_Rotation;
   Uint32 m_LastTime;
   double m_IdleTime;

//////////////////Removed
};

// Inline Methods
//
// External References
//

#endif  // _en_cube_h
