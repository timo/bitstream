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

//////////////////////////////////////////////////////////////////////////
// Name: GLEnemy 
//
// Files:
// Bugs:
// See Also:
// Type: C++-Source
//////////////////////////////////////////////////////////////////////////
// Authors:
// Date:
//////////////////////////////////////////////////////////////////////////
// Modifications:
//
/////////////////////////////////////////////////////////////////////////
#include "GLEnemy.h"                                // class implemented
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include "Texture.h"
#include "BSM.h"
#include "GLPlayer.h"

using namespace std;
/////////////////////////////// Public ///////////////////////////////////////

//============================= Lifecycle ====================================

GLEnemy::GLEnemy()
{
}// GLEnemy

GLEnemy::GLEnemy(const GLEnemy&)
{
}// GLEnemy

GLEnemy::~GLEnemy()
{
}// ~GLEnemy


//============================= Operators ====================================

GLEnemy& 
GLEnemy::operator=(const GLEnemy&rhs)
{
   if ( this==&rhs ) {
        return *this;
    }
    //superclass::operator =(rhs);

    //add local assignments

    return *this;

}// =

//============================= Operations ===================================
//============================= Access      ==================================
//============================= Inquiry    ===================================
/////////////////////////////// Protected Methods ////////////////////////////

/////////////////////////////// Private   Methods ////////////////////////////
