#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <GL/gl.h>
#include <SDL/SDL.h>

#include "Texture.h"

//Default Constructor

Texture::Texture ()
{
}

//Copy COnstructor

Texture::Texture(const Texture&rhs)
  : bpp(rhs.bpp),
    width(rhs.width),
    height(rhs.height),
    ID(rhs.ID)
{
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
    fprintf(stderr, "Texture::LoadBMP: unable to load \"%s\": %s\n", filename, SDL_GetError());
    return false;
  }

  /* GL surfaces are upsidedown and RGB, not BGR :-) */


  tmpbuf = new unsigned char[image->pitch];

  if ( tmpbuf == NULL ) {
    fprintf(stderr, "Texture::LoadBMP: could not allocate buffer\n");
    return false;
  }
  else
    {
      cout << "Alloc succeeded" << endl;
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
  
  fprintf (stderr, "Texture::LoadBMP: loaded \"%s\" correctly\n", filename);
  
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
  GLuint type=GL_RGBA;
  
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

      fprintf (stderr, "Texture::LoadTGA: \"%s\" does not exist.\n", filename);
      return false;							
    }
    
    else {
      
      // If anything failed, close the file
      fclose (file);

      fprintf (stderr, "Texture::LoadTGA: could not load \"%s\" correctly, general failure.\n", filename);
      
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
		
    fprintf (stderr, "Texture::LoadTGA: \"%s\"'s height or width is less than zero, or the TGA is not 24 or 32 bits.\n", filename);
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
    
    fprintf (stderr, "Texture::LoadTGA: Storate memory for \"%s\" does not exist or is corrupted.\n", filename);
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

  fprintf (stderr, "Texture::LoadTGA: Loaded \"%s\" correctly.\n", filename);
  return true;
}


unsigned int 
Texture::getID()const
{

  return ID;

}
