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
// Name: en_weapon 
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
// Modifications:
//
//
///////////////////////////////////////////////////////////////////////////
#ifndef _en_weapon_h_
#define _en_weapon_h_
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
class en_weapon : public GLEntity
{
public:

// Lifecycle

   en_weapon(const GLdouble&, const GLdouble&, const GLdouble&);
   en_weapon(const en_weapon&);            // copy constructor
   ~en_weapon();

// Operator
   
   en_weapon&   operator=(const en_weapon&);     // assignment operator

// Operations

	void draw();



	GLdouble getRho()const;
	GLdouble GetLongestRadius();

	virtual GLdouble getX();
	virtual GLdouble getY();
	virtual GLdouble getZ();
	virtual bool isAlive();

	void ApplyDamage(const GLdouble &);
	GLdouble GetHitDamage();

protected:
// Protected Methods
private:
// Private Methods

	BSM m_model;
	GLdouble m_Vel;
	GLdouble m_xAngle;
	GLdouble m_yAngle;
	GLdouble m_xBase;
	GLdouble m_yBase;
	GLdouble m_zBase;
	GLdouble m_xPos;
	GLdouble m_yPos;
	GLdouble m_zPos;
	GLdouble m_rho;
	GLdouble m_dDamage;
	int m_SourceExplosion;
	int m_HitGround;
   position m_Blast;
   Uint32 m_lastTime;


//////////////////Removed
};

// Inline Methods
//
// External References
//

#endif  // _en_weapon_h
