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
	void addPoint(const double &);
	unsigned size()const;


// Access

// Inquiry

protected:
// Protected Methods
private:

	double *m_ptrVertex;        //Vertex array
   double *m_ptrPoints;      //which vertex
	unsigned m_uVSize;
	unsigned m_uPSize;

// Private Methods

	int resize(const unsigned &, const unsigned &flag , unsigned &);

//////////////////Removed
};

// Inline Methods
//
// External References
//

#endif  // _BSM_h
