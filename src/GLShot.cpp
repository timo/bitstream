//////////////////////////////////////////////////////////////////////////
// Name: GLShot 
//
// Files:
// Bugs:
// See Also:
// Type: C++-Source
//////////////////////////////////////////////////////////////////////////
// Authors:
// Date:
//////////////////////////////////////////////////////////////////////////
// Modifications:
//
/////////////////////////////////////////////////////////////////////////
#include "GLShot.h"                                // class implemented
#include <GL/gl.h>
#include <GL/glu.h>
#include "Texture.h"
#include "BSM.h"

/////////////////////////////// Public ///////////////////////////////////////

//============================= Lifecycle ====================================

GLShot::GLShot()
{
  shot.LoadBSM ("data/player/player.bsm");

}// GLShot

GLShot::GLShot(const GLShot&)
{
}// GLShot

GLShot::~GLShot()
{
}// ~GLShot


//============================= Operators ====================================

GLShot& 
GLShot::operator=(const GLShot&rhs)
{
   if ( this==&rhs ) {
        return *this;
    }
    //superclass::operator =(rhs);

    //add local assignments

    return *this;

}// =

//============================= Operations ===================================

void 
GLShot::draw(){

  shot.draw();

}

//============================= Access      ==================================
//============================= Inquiry    ===================================
/////////////////////////////// Protected Methods ////////////////////////////

/////////////////////////////// Private   Methods ////////////////////////////
