/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: t; c-basic-offset: 3 -*- */


#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glu.h>

//------------------------------------------------------------------//
//- class TEXTURE --------------------------------------------------//
//------------------------------------------------------------------//
//- The main texture class, has loading support for truevision	   -//
//- targas (.tga), and the Microsoft Bitmap (.bmp) format.	   -//
//------------------------------------------------------------------//
class TEXTURE {

 public:

  GLubyte* data;			//Image data (up to 32 bits)
  unsigned int bpp;		//Image color depth in bits per pixel
  unsigned int width;		//Image width
  unsigned int height;	//Image height
  unsigned int ID;		//Texture ID used to select a texture

  bool LoadTGA(char* filename, GLfloat minFilter, GLfloat maxFilter);
  bool LoadBMP(char* filename, GLfloat minFilter, GLfloat maxFilter);
  
  TEXTURE ();

  ~TEXTURE();
};

#endif

