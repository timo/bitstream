/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: t; c-basic-offset: 3 -*- */
///////////////////////////////////////////////////////////////////////////
// Name: Texture
///////////////////////////////////////////////////////////////////////////

#ifndef _Texture_h_
#define _Texture_h_

#include <GL/glu.h>

//------------------------------------------------------------------//
//- class TEXTURE --------------------------------------------------//
//------------------------------------------------------------------//
//- The main texture class, has loading support for truevision	   -//
//- targas (.tga), and the Microsoft Bitmap (.bmp) format.	   -//
//------------------------------------------------------------------//

class Texture {

public:
	Texture();
   Texture(const Texture&);  // Copy Constructor
	~Texture();

	bool LoadTGA(char* filename, const GLfloat &minFilter, const GLfloat &maxFilter);
	bool LoadBMP(char* filename, const GLint &minFilter, const GLint &maxFilter);
	bool LoadPCX(char* filename, const GLint &minFilter, const GLint &maxFilter);
	unsigned int getID()const;

protected:

private:

  GLubyte* data;			//Image data (up to 32 bits)
  unsigned int bpp;		//Image color depth in bits per pixel
  unsigned int width;		//Image width
  unsigned int height;	//Image height
  unsigned int ID;		//Texture ID used to select a texture

};

#endif

