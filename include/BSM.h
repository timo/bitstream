/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: t; c-basic-offset: 3 -*- */
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
	bool LoadBSM(char *filename);
	void addVertex(const double &);
	void addPoint(const int &);
	unsigned size()const;


// Access

// Inquiry

protected:
// Protected Methods
private:

	vector< float > m_ptrVertex;        //Vertex array
   vector< int > m_ptrPoints;          //which vertex
	vector< vector <int> > m_vBSM;

// Private Methods

	GLvoid FindNormal( GLuint i, GLfloat *normals);

//////////////////Removed
};

// Inline Methods
//
// External References
//

#endif  // _BSM_h
