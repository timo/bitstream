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

   en_cube(const GLdouble&x, const GLdouble&y, const GLdouble&z);
   en_cube(const en_cube&);            // copy constructor
   ~en_cube();

// Operator
   
   en_cube&   operator=(const en_cube&);     // assignment operator

// Operations

	void en_attack();
   void en_idle();
	void en_move();
   void draw();

// Access

// Inquiry

protected:
// Protected Methods
private:
// Private Methods
	BSM m_model;
	GLdouble m_xVel;
	GLdouble m_yVel;
	GLdouble m_zVel;
	GLdouble m_xTilt;
	GLdouble m_yTilt;
	GLdouble m_zTilt;
	GLdouble m_xAcc;
	GLdouble m_yAcc;
	GLdouble m_zAcc;
	GLdouble m_xPos;
	GLdouble m_yPos;
	GLdouble m_zPos;
   Uint32 m_dLasttime;

//////////////////Removed
};

// Inline Methods
//
// External References
//

#endif  // _en_cube_h
