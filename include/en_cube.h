/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: t; c-basic-offset: 3 -*- */
///////////////////////////////////////////////////////////////////////////
// Name: en_cube 
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
// Modifications:
//
//
///////////////////////////////////////////////////////////////////////////
#ifndef _en_cube_h_
#define _en_cube_h_

// System Includes
//

// Project Includes
//

#include "BSM.h"
#include "GLEnemy.h"
#include "physics.h"

// Local Includes
//

// Forward References
//

/**   
  *    @author 
  *    @date 
  */
class en_cube : public GLEnemy
{
public:

// Lifecycle
   en_cube(const double &x=0, const double &y=0, const double &z=0);
   en_cube(const position &);
   en_cube(const en_cube&);            // copy constructor
   virtual ~en_cube();

// Operator
   
   en_cube&   operator=(const en_cube&);     // assignment operator

// Operations

	void en_attack_state();
   void en_idle_state();
	void en_react_state();
	void en_move();

   void draw();
   GLdouble GetLongestRadius();
// Access

	GLdouble getX();
	GLdouble getY();
	GLdouble getZ();

	void ApplyDamage(const GLdouble &);
   GLdouble GetHitDamage();
	bool isAlive();

	//	void SetDestroyed(const GLint &i);
	//	GLint GetDestroyed();
protected:
// Protected Methods
private:
// Private Methods

	void build();  // Common constructor code
	enum mood {IDLE, REACT, ATTACK};
	enum color {RED=0, GREEN, BLUE, ALPHA};

	BSM m_model;
   velocity m_Velocity;
   acceleration m_Acceleration;
   position m_Position;
   rotation m_Rotation;
   Uint32 m_LastTime;
	GLdouble m_DeltaSeconds;
   GLdouble m_IdleTime;
	GLdouble m_dDamage;
	GLfloat m_Color[4];
	mood m_Behavior;
	//   static GLint m_iDestroyed;

//////////////////Removed
};

// Inline Methods
//
// External References
//

#endif  // _en_cube_h
