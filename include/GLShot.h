/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: t; c-basic-offset: 3 -*- */
///////////////////////////////////////////////////////////////////////////
// Name: GLShot 
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
// Modifications:
//
//
///////////////////////////////////////////////////////////////////////////
#ifndef _GLShot_h_
#define _GLShot_h_
#include <SDL/SDL.h>
#include "GLEntity.h"
#include "BSM.h"
// System Includes
//

// Project Includes
//

// Local Includes
//

// Forward References
//

/**   
  *    @author 
  *    @date 
  */
class GLShot : public GLEntity
{
public:

// Lifecycle

   GLShot();
   GLShot(const GLShot&);            // copy constructor
   ~GLShot();

// Operator
   
   GLShot&   operator=(const GLShot&);     // assignment operator

// Operations

	void draw();

// Access

// Inquiry

protected:
// Protected Methods
private:
// Private Methods

	BSM shot;
	GLdouble m_Vel;
	GLdouble m_xAngle;
	GLdouble m_yAngle;
	GLdouble m_rho;


//////////////////Removed
};

// Inline Methods
//
// External References
//

#endif  // _GLShot_h
