/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: t; c-basic-offset: 3 -*- */
///////////////////////////////////////////////////////////////////////////
// Name: GLEntity 
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
// Modifications:
//
//
///////////////////////////////////////////////////////////////////////////
#ifndef _GLEntity_h_
#define _GLEntity_h_

// System Includes
//
#include <GL/gl.h>
// Project Includes
//

// Local Includes
//

// Forward References
//

/**   
  *    Jeff Mrochuk
  *    Nov 2, 2001
  */
class GLEntity
{
public:

// Lifecycle

   GLEntity(const GLdouble &x=0, const GLdouble &y=0, const GLdouble &z=0);
   GLEntity(const GLEntity&);            // copy constructor
   virtual ~GLEntity();

// Operator
   
   GLEntity&   operator=(const GLEntity&);     // assignment operator

// Operations

	void drawAll()const;

	GLint shift(const GLdouble &x=0, const GLdouble &y=0, const GLdouble &z=0);
	void tilt(const GLdouble &x=0, const GLdouble &y=0);

// Access

	GLdouble getX()const;
	GLdouble getY()const;
	GLdouble getZ()const;
	GLdouble getXtilt()const;
	GLdouble getYtilt()const;

// Inquiry

protected:
// Protected Methods
private:
// Private Methods

	GLdouble m_dLastTime, m_dThisTime;
	GLdouble m_dX;
	GLdouble m_dY;
	GLdouble m_dZ;

	//	static GLdouble m_dXtilt;
	//	static GLdouble m_dYtilt;

	GLint m_idraw;



//////////////////Removed
};

// Inline Methods
//
// External References
//

#endif  // _GLEntity_h
