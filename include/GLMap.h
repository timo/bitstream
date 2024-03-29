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
// Name: GLMap 
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
// Modifications:
//
//
///////////////////////////////////////////////////////////////////////////
#ifndef _GLMap_h_
#define _GLMap_h_

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
class GLMap : public GLEntity
{
public:

// Lifecycle

   GLMap(const int &iMapnum =1);
   GLMap(const GLMap&);            // copy constructor
   ~GLMap();

// Operator
   
   GLMap&   operator=(const GLMap&);     // assignment operator

// Operations
	void draw(GLdouble dZ)const;
// Access

// Inquiry

protected:
// Protected Methods
private:
// Private Methods


//////////////////Removed
};

// Inline Methods
//
// External References
//

#endif  // _GLMap_h
