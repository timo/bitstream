/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: t; c-basic-offset: 3 -*- */
#ifndef MATH_H
#define MATH_H

#include <stdlib.h>

#include <GL/gl.h>

#define PI 3.1415926535897932384626433832795f
#define PIOVER180 0.0174532925199432957692369076848861f
#define PIUNDER180 57.2957795130823208767981548141052f
#define	VERTEX3D VECTOR3D

#define MIN(a, b)  (((a) < (b)) ? (a) : (b))
#define MAX(a, b)  (((a) > (b)) ? (b) : (a))

#define RANDOM_FLOAT (((float) rand () - (float) rand ()) / RAND_MAX)
#define CHECK_RANGE(x,min,max) (( x= (x < min  ? min : x < max ? x : max)))
#define DEG_TO_RAD(angle)  ((angle) * PIOVER180)
#define RAD_TO_DEG(radians) ((radians) * PIUNDER180)
#define SQUARE(number) (number * number)

//------------------------------------------------------------------//
//- class VECTOR3D -------------------------------------------------//
//------------------------------------------------------------------//
//- A class for all three dimensional vectors.  This will have some-//
//- very nice features so that we can add/multiply/subtract/divide -//
//- vectors together now! (Also used for vertices)				   -//
//------------------------------------------------------------------//

class VECTOR {

 public:

  float vector[3];

  float ComputeLength(void);

  VECTOR inline operator+ (const VECTOR &v);
  VECTOR inline operator- (const VECTOR &v);
  VECTOR inline operator* (const float scalar);
  VECTOR inline operator* (const VECTOR &v);
  VECTOR inline operator/ (const VECTOR &v);

  VECTOR ();
  VECTOR (float x, float y, float z);
	
};

//------------------------------------------------------------------//
//- class VECTOR3D -------------------------------------------------//
//------------------------------------------------------------------//
//- A class for all three dimensional vectors.  This will have some-//
//- very nice features so that we can add/multiply/subtract/divide -//
//- vectors together now! (Also used for vertices)		   -//
//------------------------------------------------------------------//
class VERTEX {

 public:
  float vertex[3];

  VERTEX inline operator+ (const VERTEX &v);
  VERTEX inline operator- (const VERTEX &v);
  VERTEX inline operator* (const float scalar);
  VERTEX inline operator* (const VERTEX &v);
  VERTEX inline operator/ (const VERTEX &v);
  
  void SendToOGL (void);

  VERTEX ();
  VERTEX (float x, float y, float z);
};

//------------------------------------------------------------------//
//- class VECTOR3D -------------------------------------------------//
//------------------------------------------------------------------//
//- A class for 4x4 matrices.					   -//
//------------------------------------------------------------------//
class MATRIX4X4 {

 public:
  float matrix[16];

  void LoadZero (void);
  void LoadIdentity (void);

  friend MATRIX4X4 operator+ (const MATRIX4X4 &m1, const MATRIX4X4 &m2);
  friend MATRIX4X4 operator- (const MATRIX4X4 &m1, const MATRIX4X4 &m2);
  friend MATRIX4X4 operator* (const MATRIX4X4 &m1, const float scalar);
  friend MATRIX4X4 operator* (const MATRIX4X4 &m1, const MATRIX4X4 &m2);

  MATRIX4X4();
};

GLint Random (GLint, GLint);

#endif
