/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: t; c-basic-offset: 3 -*- */
///////////////////////////////////////////////////////////////////////////
// Name: GLPlayer 
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
// Modifications:
//
//
///////////////////////////////////////////////////////////////////////////
#ifndef _GLPlayer_h_
#define _GLPlayer_h_

// System Includes
//

// Project Includes
//
#include "GLEntity.h"
// Local Includes
//

// Forward References
//

/**   
  *    @author 
  *    @date 
  */
class GLPlayer : public GLEntity
{
public:

// Lifecycle

   GLPlayer(const GLdouble &x=0, const GLdouble &y=0, const GLdouble &z=0);
   GLPlayer(const GLPlayer&);            // copy constructor
   ~GLPlayer();

// Operator
   
   GLPlayer&   operator=(const GLPlayer&);     // assignment operator


// Operations

	void move(const GLint &x=0, const GLint &y=0, const GLint &z=0);
	void setVel(const GLdouble &x=0, const GLdouble &y=0);
	void draw()const;
	void collide();

// Access

// Inquiry

protected:
// Protected Methods
private:
// Private Methods

   GLdouble m_dLasttime, m_dThistime;
	GLdouble m_dXvel, m_dYvel;
   GLdouble m_dOverrideX, m_dOverrideY;


//////////////////Removed
};

// Inline Methods
//
// External References
//

#endif  // _GLPlayer_h
