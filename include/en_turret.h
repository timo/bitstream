/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: t; c-basic-offset: 3 -*- */
///////////////////////////////////////////////////////////////////////////
// Name: en_cube 
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
// Modifications:
//
//
///////////////////////////////////////////////////////////////////////////
#ifndef _en_turret_h_
#define _en_turret_h_

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
class en_turret : public GLEnemy
{
public:

// Lifecycle
   en_turret(const double &x=0, const double &y=0, const double &z=0);
   en_turret(const position &);
   en_turret(const en_turret&);            // copy constructor
   virtual ~en_turret();

// Operator
   
   en_turret&   operator=(const en_turret&);     // assignment operator

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
//////////////////Removed
};

// Inline Methods
//
// External References
//

#endif  // _en_turret_h
