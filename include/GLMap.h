/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: t; c-basic-offset: 3 -*- */
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
	void draw()const;
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
