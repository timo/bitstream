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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <GL/gl.h>
#include <SDL/SDL.h>
#include <fstream>
#include "Texture.h"

using namespace std;
//Default Constructor

Texture::Texture ()
{
}

//Copy COnstructor

Texture::Texture(const Texture&rhs)
{
  bpp = rhs.bpp;
  width = rhs.width;
  height = rhs.height;
  ID = rhs.ID;
}

Texture::~Texture () 
{	
  if (data) {
    delete data;	
  }
}

bool 
Texture::LoadBMP (char *filename, const GLint &minFilter, const GLint &maxFilter) {

  /*
    Taken from lesson 7 SDL port
   */

  Uint8 *rowhi, *rowlo;
  Uint8 *tmpbuf, tmpch;
  SDL_Surface *image;
  int i, j;

  image = SDL_LoadBMP (filename);
  if (image == NULL) {
#ifdef _linux_
    fprintf(stderr, "Texture::LoadBMP: unable to load \"%s\": %s\n", filename, SDL_GetError());
#endif
    return false;
  }

  /* GL surfaces are upsidedown and RGB, not BGR :-) */


  tmpbuf = new unsigned char[image->pitch];

  if ( tmpbuf == NULL ) {
#ifdef _linux_
    fprintf(stderr, "Texture::LoadBMP: could not allocate buffer\n");
#endif
    return false;
  }

  rowhi = (Uint8 *)image->pixels;
  rowlo = rowhi + (image->h * image->pitch) - image->pitch;

  for ( i=0; i<(image->h)/2; ++i ) {
    for ( j=0; j<(image->w); ++j ) {
      tmpch = rowhi[j*3];
      rowhi[j*3] = rowhi[j*3+2];
      rowhi[j*3+2] = tmpch;
      tmpch = rowlo[j*3];
      rowlo[j*3] = rowlo[j*3+2];
      rowlo[j*3+2] = tmpch;
    }

    memcpy(tmpbuf, rowhi, image->pitch);
    memcpy(rowhi, rowlo, image->pitch);
    memcpy(rowlo, tmpbuf, image->pitch);

    rowhi += image->pitch;
    rowlo -= image->pitch;
  }

  delete tmpbuf;

  // Create Texture

  glGenTextures (1, &ID);
  glBindTexture(GL_TEXTURE_2D, ID);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, maxFilter);
  
  glTexImage2D (GL_TEXTURE_2D, 0,  3, image->w, image->h, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

  //Bind the texture to a texture object 
#ifdef _linux_  
  fprintf (stderr, "Texture::LoadBMP: loaded \"%s\" correctly\n", filename);
#endif
  return true;
}


//------------------------------------------------------------------//
//- bool LoadTGA(char*, GLfloat, GLfloat) --------------------------//
//------------------------------------------------------------------//
//- Description: This function loads a truevision TARGA into the   -//
//-				 Texture class object that it represents.		   -//
//------------------------------------------------------------------//
//- Big thanks to NeHe for this one								   -//
//------------------------------------------------------------------//
bool
Texture::LoadTGA (char* filename, const GLfloat &minFilter, const GLfloat &maxFilter) {
    
  //Uncompressed TGA header
  GLubyte TGAheader[12]={0,0,2,0,0,0,0,0,0,0,0,0};	
  //Used to compare TGA header
  GLubyte TGAcompare[12];
  //The first six useful bytes from the header
  GLubyte header[6];
  //Holds the bpp of the TGA
  GLuint bytesPerPixel;
  //Used to store image size while in RAM
  GLuint imageSize;
  //Temp variable
  GLuint temp;
  //Set the default OpenGL mode to RBGA (32 BPP)
  GLenum type=GL_RGBA;
  
  // Open The TGA File
  FILE* file = fopen (filename, "rb");

  // Does File Even Exist?
  // Are There 12 Bytes To Read?
  // Does The Header Match What We Want?
  // If So Read Next 6 Header Bytes
  if (file==NULL 
      || fread (TGAcompare, 1, sizeof (TGAcompare), file) !=sizeof (TGAcompare) 
      || memcmp (TGAheader, TGAcompare, sizeof (TGAheader)) !=0
      || fread (header, 1, sizeof (header), file) != sizeof (header)) {

    // Did The File Even Exist? *Added Jim Strong*
    if (file == NULL) {
#ifdef _linux_
      fprintf (stderr, "Texture::LoadTGA: \"%s\" does not exist.\n", filename);
#endif
      return false;							
    }
    
    else {
      
      // If anything failed, close the file
      fclose (file);
#ifdef _linux_
      fprintf (stderr, "Texture::LoadTGA: could not load \"%s\" correctly, general failure.\n", filename);
#endif
      return false;						
    }
  }

  // Determine The TGA Width	(highbyte*256+lowbyte)
  width = header[1] * 256 + header[0];
  // Determine The TGA Width	(highbyte*256+lowbyte)		// Determine The TGA Height	(highbyte*256+lowbyte)		// Determine The TGA Width	(highbyte*256+lowbyte)		// Determine The TGA Height	(highbyte*256+lowbyte)
  height= header[3] * 256 + header[2];
    
  // Is The Width Less Than Or Equal To Zero
  // Is The Height Less Than Or Equal To Zero
  // Is The TGA 24 or 32 Bit?
  if (width <= 0	
      || height <= 0	
      || (header[4] != 24 && header[4] != 32)) {

    // If Anything Failed, Close The File
    fclose (file);
#ifdef _linux_		
    fprintf (stderr, "Texture::LoadTGA: \"%s\"'s height or width is less than zero, or the TGA is not 24 or 32 bits.\n", filename);
#endif
    return false;							
  }

  // Grab The TGA's Bits Per Pixel (24 or 32)
  bpp = header[4];		

  // Divide By 8 To Get The Bytes Per Pixel
  bytesPerPixel = bpp  /8;
  // Calculate The Memory Required For The TGA Data
  imageSize = width * height * bytesPerPixel;
  
  // Reserve Memory To Hold The TGA Data
  data = new GLubyte [imageSize];

  // Does The Storage Memory Exist?
  // Does The Image Size Match The Memory Reserved?
  if (data == NULL 
      || fread (data, 1, imageSize, file) != imageSize) {

    // Was Image Data Loaded
    // If So, Release The Image Data
    if (data != NULL) free (data);
#ifdef _linux_    
    fprintf (stderr, "Texture::LoadTGA: Storate memory for \"%s\" does not exist or is corrupted.\n", filename);
#endif
    // Close The File    
    fclose(file);
    return false;	
  }

  // Loop Through The Image Data
  // Swaps The 1st And 3rd Bytes ('R'ed and 'B'lue)
  // Temporarily Store The Value At Image Data 'i'
  for (GLuint i=0; i<(unsigned int) imageSize; i += bytesPerPixel) {

    temp = data[i];
    // Set The 1st Byte To The Value Of The 3rd Byte
    data[i] = data[i + 2];
    // Set The 3rd Byte To The Value In 'temp' (1st Byte Value)
    data[i + 2] = temp;
  }
  
  fclose (file);

  // Build A Texture From The Data
	
  //Generate OpenGL texture IDs
  glGenTextures (1, &ID);

  //Bind the texture to a texture object 
  glBindTexture (GL_TEXTURE_2D, ID);

  //Filtering for if texture is bigger than should be
  glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
  //Filtering for if texture is smaller than it should be
  glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, maxFilter);
	
  //Was the TGA 24 bpp?
  if (bpp == 24) type = GL_RGB;							

  glTexImage2D (GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, data);
#ifdef _linux_
  fprintf (stderr, "Texture::LoadTGA: Loaded \"%s\" correctly.\n", filename);
#endif
  return true;
}


GLuint 
Texture::getID()const
{

  return ID;

}

#if _PCX_SUPPORT_

unsigned char *readpcx( ifstream &file, unsigned char *palette,unsigned short int *length, unsigned short int *height);

bool
Texture::LoadPCX ( char* filename, const GLint &minFilter, const GLint &maxFilter)
{

  ifstream filepcx(filename, ios::binary);
  if(!filepcx){
    cout << "Unable to open file" << endl;
    return false;
  }

  unsigned char *image;
  unsigned short int width, height;
  unsigned char palette[768];

  if ((image=readpcx(filepcx,palette,&width,&height))==NULL)
    {
      printf("Error loading file!\n");
      return(1);
    }
  

  filepcx.close();

  unsigned char *rgbimage;
  rgbimage = new unsigned char[3*(width)*(height)];

  //Convert to RGB

  for(int i=0; i < (width*height); i++){

    rgbimage[i*3+0] = palette[image[i]*3+0];
    rgbimage[i*3+1] = palette[image[i]*3+1];
    rgbimage[i*3+2] = palette[image[i]*3+2];

  }


 glGenTextures (1, &ID);
 glBindTexture(GL_TEXTURE_2D, ID);

 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  
 glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
 glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, maxFilter);

 //If not 256x256 convert

  if(width!=256 || height!=256)
    {
      unsigned char *stretched = new unsigned char[3*256*256];

      gluScaleImage(GL_RGB, width, height, GL_UNSIGNED_BYTE, rgbimage, 256, 256, GL_UNSIGNED_BYTE, stretched);
    

      glTexImage2D (GL_TEXTURE_2D, 0,  3, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, stretched);


      if(stretched){
	delete stretched;
      }
      
    }
  else{  // Don't waste time converting

    glTexImage2D (GL_TEXTURE_2D, 0,  3, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, rgbimage);

  }


  //Clean up memory

  if(rgbimage){
    delete rgbimage;
  }

  if(image){
    delete image;

  }

#ifdef _linux_
 fprintf (stderr, "Texture::LoadPCX: loaded \"%s\" correctly\n", filename);
#endif
 return true;
 
    
}



void readpcximage( ifstream &file, unsigned char * target,const int &size)
{
  unsigned char buf;
  unsigned int counter;
  int i=0;
  while(i<size)  /* Image not entirely read? */
    {
      /* Get one byte */
      file.read(&buf,1);
      /* Check the 2 most significant bits */
      if ((buf&192)==192)
	{
	  /* We have 11xxxxxx */
	  counter=(buf&63);         /* Number of times to repeat next byte */
	  file.read(&buf,1);     /* Get next byte */
	  for(;counter>0;counter--) /* and copy it counter times */
	    {
	      ((char*)target)[i]=buf;
	      i++;   /* increase the number of bytes written */
	    }
	}
      else
	{
	  /* Just copy the byte */
	  ((char*)target)[i]=buf;
	  i++;   /* Increase the number of bytes written */
	}
    }

}


unsigned char *readpcx(ifstream &file,unsigned char *mypalette,unsigned short int *width , unsigned short int *height)
{

  typedef struct
  {
    char signature;
    char version;
    char encoding;
    char bytes_per_pixel;
    unsigned short int xmin;
    unsigned short int ymin;
    unsigned short int xmax;
    unsigned short int ymax;
    unsigned short int vres;
    unsigned short int hres;
    char palette[48];
    char reserved;
    char color_layers;
    unsigned short int bytes_per_line;
    unsigned short int palette_type;
    char unused[58];
  }PCX_Header;

  /* Returns NULL if failed, otherwise a pointer to the loaded image */
  PCX_Header header;
  unsigned char *target;


  file.seekg(0);

  // file.read(reinterpret_cast<unsigned char *>(&header),sizeof(PCX_Header));
  file.read((&header),sizeof(PCX_Header));
  /* Check if this file is in pcx format */
  if((header.signature!=0x0a)||(header.version!=5)){
    cout << "Invalid PCX" << endl;
    return(NULL);
   }
  
  else
    {/* it is! */
      /* Return height and width */
      
      *width=header.xmax+1-header.xmin;
      *height=header.ymax+1-header.ymin;

      target = new unsigned char[(*width)*(*height)];
      /* Read the image */
      
      readpcximage(file,target,(*width)*(*height));
      
      /* Get the palette */
      // fread(palette,1,768,file);
      
      file.seekg(-768, ios::end);
      file.read(mypalette, 768);
      
      /* PCX succesfully read! */
      
      return(target);
    }
}
#endif
