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
// Name: BSMPiece 
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
#include "BSMPiece.h"                                // class implemented

using namespace std;
/////////////////////////////// Public ///////////////////////////////////////

//============================= Lifecycle ====================================

BSMPiece::BSMPiece()
  :m_dDamage(100)
{
}// BSMPiece

BSMPiece::BSMPiece(const BSMPiece&rhs)
  :m_dDamage(rhs.m_dDamage)
{

  for(unsigned i=0; i < rhs.m_ptrPoints.size(); i++){
    m_ptrPoints.push_back(rhs.m_ptrPoints[i]);
     } 
}
// BSMPiece

BSMPiece::~BSMPiece()
{
}// ~BSMPiece


//============================= Operators ====================================

BSMPiece& 
BSMPiece::operator=(const BSMPiece&rhs)
{
   if ( this==&rhs ) {
        return *this;
    }


   m_dDamage=rhs.m_dDamage;
   for(unsigned i=0; i < rhs.m_ptrPoints.size(); i++){
     m_ptrPoints.push_back(rhs.m_ptrPoints[i]);
   } 

    return *this;

}// =

int
BSMPiece::operator[](const int &index){

  return m_ptrPoints[index];

}

bool 
BSMPiece::isAlive()const{

  if(m_dDamage > 0) return true;

  return false;

}

void
BSMPiece::kill(){

  m_dDamage=0;

}
	
void
BSMPiece::hit(){

  m_dDamage-=15;

}
bool 
BSMPiece::addVertex(const int &vert){

  m_ptrPoints.push_back(vert);

  return true;
}

vector < GLint >  *
BSMPiece::get_vec(){

  return &m_ptrPoints;

}

void
BSMPiece::clear_vec(){

  m_ptrPoints.clear();

}


unsigned
BSMPiece::size(){

  return m_ptrPoints.size();

}

//============================= Inquiry    ===================================


/////////////////////////////// Protected Methods ////////////////////////////

/////////////////////////////// Private   Methods ////////////////////////////
