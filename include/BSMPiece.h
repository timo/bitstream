/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: t; c-basic-offset: 3 -*- */
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

	bool isAlive()const;
	void kill();
	bool addVertex(const int &);
   vector <int>  *get_vec();
	void clear_vec();
	unsigned size();


// Access

// Inquiry

protected:
// Protected Methods
private:
// Private Methods

	GLdouble m_dDamage;
   vector< int > m_ptrPoints;          //which vertex

//////////////////Removed
};

// Inline Methods
//
// External References
//

#endif  // _BSMPiece_h