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
// Name: BSMPiece 
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
// Modifications:
//
//
///////////////////////////////////////////////////////////////////////////
#ifndef _BSMPiece_h_
#define _BSMPiece_h_
#include <vector>
#include <GL/gl.h>
using namespace std;
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
class BSMPiece
{
public:

// Lifecycle

   BSMPiece();
   BSMPiece(const BSMPiece&);            // copy constructor
   ~BSMPiece();

// Operator
   
   BSMPiece&   operator=(const BSMPiece&);     // assignment operator
	int operator[](const int &);


// Operations


	void kill();
	void hit();
	bool addVertex(const int &);
	void clear_vec();



// Access

	bool isAlive()const;
        vector < GLint > *get_vec();
	unsigned size();

// Inquiry

protected:
// Protected Methods
private:
// Private Methods

	GLdouble m_dDamage;
   vector< GLint > m_ptrPoints;          //which vertex

//////////////////Removed
};

// Inline Methods
//
// External References
//

#endif  // _BSMPiece_h
