

#include <GL/gl.h>
#include <iostream>
#include <stdio.h>
#include <stdarg.h>
#include "text.h"
#include "Texture.h"

extern Texture text;
static GLuint  base; 

using namespace std;
/* function to build our font list */
GLvoid BuildFont( GLvoid )
{
    GLuint loop;
    float cx;    // Holds Our X Character Coord 
    float cy;    // Holds Our Y Character Coord


    base  = glGenLists( 256 );

    glBindTexture( GL_TEXTURE_2D, text.getID());

    for ( loop = 0; loop < 256; loop++ )
        {


	    cx = 1 - ( float )( loop % 16 ) / 16.0f;
	    cy = 1 - ( float )( loop / 16 ) / 16.0f;
	    // Font list
	    glNewList( base + ( 255 - loop ), GL_COMPILE );

	      glBegin( GL_QUADS );
	        glTexCoord2f( cx - 0.0625, cy );
		glVertex2i( 0, 0 );

		glTexCoord2f( cx, cy );
		glVertex2i( 16, 0 );

		glTexCoord2f( cx, cy - 0.0625f );
		glVertex2i( 16, 16 );

		glTexCoord2f( cx - 0.0625f, cy - 0.0625f);
		glVertex2i( 0, 16 );
	      glEnd( );

	      glTranslated( 10, 0, 0 );
	    glEndList( );
        }
}

/* function to recover memory form our list of characters */
GLvoid KillFont( GLvoid )
{
    glDeleteLists( base, 256 ); /* Delete All 256 Display Lists */

    return;
}

/* Function to print the string */
GLvoid glPrint( GLint x, GLint y,int set, char *instring, ...  )
{
  if ( set > 1 )  // No segfaulting, jerk
	set = 1;

  char string[256];   // ... processing
  va_list ap;    

  if ( string == NULL )
	return;
 
    va_start( ap, instring );

    vsprintf( string, instring, ap );
    va_end( ap );

    glEnable(GL_TEXTURE_2D);
    glBindTexture( GL_TEXTURE_2D, text.getID() );

    glDisable( GL_DEPTH_TEST );
    glBlendFunc(GL_SRC_ALPHA , GL_ONE);
    glDisable( GL_LIGHTING );

    glMatrixMode( GL_PROJECTION );
    glPushMatrix( );

    glLoadIdentity( );
    glOrtho( 0, 1024, 0, 768, -1, 1 );

    glMatrixMode( GL_MODELVIEW );
    glPushMatrix( );
    glLoadIdentity( );

    glTranslated( x, y, 0 );

    // Choose The Font Set 
    glListBase( base - 32 + ( 128 * set ) );

    // Write The Text To The Screen 
    glCallLists( strlen( string ), GL_BYTE, string );

    glMatrixMode( GL_PROJECTION );
    glPopMatrix( );

    glMatrixMode( GL_MODELVIEW );
    glPopMatrix( );


    glEnable( GL_DEPTH_TEST );
    glBlendFunc(GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_LIGHTING );
    glDisable(GL_TEXTURE_2D);
} 
