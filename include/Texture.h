/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: t; c-basic-offset: 3 -*- */

/*
   Bitstream:  An OpenGL Space Action Game
   http://icculus.org/bitstream/

   Copyright (C) 2001, 2002 Jeff Mrochuk
   
   This file is part of bitstream.     Bitstream is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.     
   
   Bitstream is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.     
   You should have received a copy of the GNU General Public License along with Bitstream; if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

Jeff Mrochuk
jm@icculus.org

*/

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

#define _PCX_SUPPORT_ 0

class Texture {

public:
	Texture();
   Texture(const Texture&);  // Copy Constructor
	~Texture();

	bool LoadTGA(char* filename, const GLfloat &minFilter, const GLfloat &maxFilter);
	bool LoadBMP(char* filename, const GLint &minFilter, const GLint &maxFilter);
#if _PCX_SUPPORT_
	bool LoadPCX(char* filename, const GLint &minFilter, const GLint &maxFilter);
#endif
	GLuint getID()const;

protected:

private:

  GLubyte* data;			//Image data (up to 32 bits)
  unsigned int bpp;		//Image color depth in bits per pixel
  unsigned int width;		//Image width
  unsigned int height;	//Image height
  GLuint ID;		//Texture ID used to select a texture

};

#endif

