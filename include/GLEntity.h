/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: t; c-basic-offset: 3 -*- */

/*
   Bitstream:  An OpenGL Space Action Game
   http://icculus.org/bitstream/

   Copyright (C) 2001, 2002 Jeff Mrochuk
   
   This file is part of bitstream.     Bitstream is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.     
   
   Bitstream is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.     
   You should have received a copy of the GNU General Public License along with Bitstream; if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

Jeff Mrochuk
jm@icculus.org

*/
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
#include "physics.h"
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
   GLEntity(const position &);
   GLEntity(const GLEntity&);            // copy constructor
   virtual ~GLEntity();

// Operator
   
   GLEntity&   operator=(const GLEntity&);     // assignment operator

// Operations

	void drawAll()const;
	virtual void draw();
	GLint shift(const GLdouble &x=0, const GLdouble &y=0, const GLdouble &z=0);
	void tilt(const GLdouble &x=0, const GLdouble &y=0);

// Access

	virtual GLdouble getX()const;
	virtual GLdouble getY()const;
	virtual GLdouble getZ()const;
   GLdouble getXtilt()const;
   GLdouble getYtilt()const;
   GLdouble getZtilt()const;
	virtual bool isAlive(){ return true; }
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
