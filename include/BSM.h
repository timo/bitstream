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
// Name: BSM 
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
// Modifications:
//
//
///////////////////////////////////////////////////////////////////////////
#ifndef _BSM_h_
#define _BSM_h_
#include <vector>
#include <GL/gl.h>
#include "BSMPiece.h"

// System Includes
//

// Project Includes
//

// Local Includes
//

// Forward References
//

/**   
  *    Jeff Mrochuk
  *    287048
  */
class BSM
{
public:

// Lifecycle

   BSM();
   BSM(const BSM&);            // copy constructor
   ~BSM();

// Operator
   
   BSM&   operator=(const BSM&);     // assignment operator

// Operations

	void draw();
	void hit(const int &);
	bool isAlive(const int &)const;
	bool LoadBSM(char *filename);
	void addVertex(const double &);
	void addPoint(const int &);
	unsigned size()const;


// Access

// Inquiry

	GLdouble getDamage();

protected:
// Protected Methods
private:

	vector < GLfloat > m_ptrVertex;        //Vertex array
	vector < BSMPiece > m_vBSM;
	vector < GLint > m_ptrPoints;
	vector < GLfloat > m_normals;

	GLdouble m_mainDamage;
	GLint foundnormals;

// Private Methods

	GLvoid FindNormal( GLuint i, GLfloat *normals);

//////////////////Removed
};

// Inline Methods
//
// External References
//

#endif  // _BSM_h
