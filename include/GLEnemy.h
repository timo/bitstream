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
// Name: GLEnemy 
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
// Modifications:
//
//
///////////////////////////////////////////////////////////////////////////
#ifndef _GLEnemy_h_
#define _GLEnemy_h_

// System Includes
//
#include <SDL/SDL.h>
// Project Includes
//
#include "GLEntity.h"
#include "BSM.h"
#include "physics.h"

// Local Includes
//

// Forward References
//

/**   
  *    @author 
  *    @date 
  */
class GLEnemy : public GLEntity
{
public:

// Lifecycle

	GLEnemy(const GLdouble &x=0, const GLdouble &y=0, const GLdouble &z=0);
	GLEnemy(const position &);
   GLEnemy(const GLEnemy&);            // copy constructor
   virtual ~GLEnemy();

// Operator
   
   GLEnemy&   operator=(const GLEnemy&);     // assignment operator

// Operations

	virtual void en_attack_state()=0;
   virtual void en_idle_state()=0;
   virtual void en_react_state()=0;
	virtual void en_move()=0;
	virtual void draw()=0;
	virtual GLdouble GetLongestRadius()=0;

	virtual GLdouble getX()=0;
	virtual GLdouble getY()=0;
	virtual GLdouble getZ()=0;

	virtual void ApplyDamage(const GLdouble &)=0;
	virtual GLdouble GetHitDamage()=0;
	virtual bool isAlive()=0;

	GLint GetDestroyed();
	void SetDestroyed(const GLint &);
// Access

// Inquiry

protected:
// Protected Methods
private:

	static GLint m_iDestroyed;

// Private Methods


//////////////////Removed
};

// Inline Methods
//
// External References
//

#endif  // _GLEnemy_h
