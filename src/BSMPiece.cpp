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
	

bool 
BSMPiece::addVertex(const int &vert){

  m_ptrPoints.push_back(vert);

  return true;
}

vector < int >  *
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
