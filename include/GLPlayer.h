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
// Name: GLPlayer 
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
// Modifications:
//
//
///////////////////////////////////////////////////////////////////////////
#ifndef _GLPlayer_h_
#define _GLPlayer_h_
#include <SDL/SDL.h>

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
	unsigned m_collide;
	Uint32 hitTime;


//////////////////Removed
};

// Inline Methods
//
// External References
//

#endif  // _GLPlayer_h
