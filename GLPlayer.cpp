//////////////////////////////////////////////////////////////////////////
// Name: GLPlayer 
//
// Files:
// Bugs:
// See Also:
// Type: C++-Source
//////////////////////////////////////////////////////////////////////////
// Authors: Jeff Mrochuk
// Date:    Nov 2, 2001
//////////////////////////////////////////////////////////////////////////
// Modifications:
//
/////////////////////////////////////////////////////////////////////////
#include "GLPlayer.h" 
                               // class implemented
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>

/////////////////////////////// Public ///////////////////////////////////////

//============================= Lifecycle ====================================

static const GLdouble ACCEL = 0.1;
static const GLdouble SLOW = 0.1;
static const GLdouble MAXSPEED = 8.0;

GLPlayer::GLPlayer(const GLdouble &x, const GLdouble &y, const GLdouble &z)
  :GLEntity(x, y, z)
{

#ifdef DEBUG
  cout << "GLPlayer created" << endl;
#endif

}// GLPlayer

GLPlayer::GLPlayer(const GLPlayer&)
{
}// GLPlayer

GLPlayer::~GLPlayer()
{
#ifdef DEBUG
  cout << "GLPlayer destroyed" << endl;
#endif

}// ~GLPlayer


//============================= Operators ====================================

GLPlayer& 
GLPlayer::operator=(const GLPlayer&rhs)
{
   if ( this==&rhs ) {
        return *this;
    }
    //superclass::operator =(rhs);

    //add local assignments

    return *this;

}// =



//============================= Operations ===================================


GLvoid FindNormal(GLuint indices[42], GLuint i, GLfloat *normals);


static GLfloat vdata[27] = {
   0.0, 0.0, 0.0   ,          // 0
   0.5, 0.125, -1.0,          // 1
  -0.5, 0.125, -1.0,          // 2
  -0.5,-0.125, -1.0,          // 3
   0.5,-0.125, -1.0,          // 4
   0.5, 0.0, -2.0  ,          // 5
  -0.5, 0.0, -2.0  ,          // 6
  -1.5, 0.0, -0.5  ,          // 7
   1.5, 0.0, -0.5             // 8
};

static GLuint tindices[42] = {
  0, 1, 2,   // Front Top
  0, 3, 4,   // Front Bottom
  0, 2, 3,   // Front Left 
  0, 4, 1,   // Front Right
  2, 1, 6,   // Base Top
  6, 1, 5,
  3, 6, 5,   // Base Bottom
  3, 5, 4,
  1, 8, 5,   // Right Top
  4, 5, 8,   // Right Bottom
  4, 8, 1,   // Right Front
  2, 6, 7,   // Left Top
  3, 7, 6,   // Left Bottom
  2, 7, 3    // Left Front
};

void
GLPlayer::draw()const{

  glPushMatrix();

  glTranslatef(this->getX(),this->getY(),this->getZ());

  GLuint i=0;
  GLfloat normal[3];
  GLfloat *ntemp;
  glColor3f(0.0f, 0.4f, 0.8f);
  glRotatef(-m_dXvel*2, 0.0f, 0.0f, 1.0f);
  glRotatef(m_dYvel*2, 1.0f, 0.0f, 0.0f);

  glBegin(GL_TRIANGLES);
  for (i=0; i<42; i=i+3){
    FindNormal(tindices, i, ntemp);
    normal[0] = *ntemp;
    normal[1] = *(ntemp + sizeof(GLfloat));
    normal[2] = *(ntemp + 2*sizeof(GLfloat));
    //    fprintf(stderr,"%f   %f   %f\n", normal[0], normal[1], normal[2]);
    glNormal3fv(normal);
    glVertex3fv(&vdata[(tindices[i]*3)]);
    glVertex3fv(&vdata[(tindices[i+1])*3]);
    glVertex3fv(&vdata[(tindices[i+2])*3]);
  }
  glEnd();

  glPopMatrix();

#ifdef DEBUG

  cout << "\r( " << this->getX() <<" , " << this->getY() << " , " << this->getZ() << " )";

#endif

}


// THIS DOES NOT BELONG

GLvoid FindNormal(GLuint indices[42], GLuint i, GLfloat *normals){

  GLuint x=0;
  GLuint y=1;
  GLuint z=2;
  GLfloat v1[3],v2[3]; 
  GLfloat mag, tempx, tempy, tempz;

  v1[x] = vdata[(indices[i])*3] - vdata[(indices[i+y])*3];
  v2[x] = vdata[(indices[i])*3] - vdata[(indices[i+z])*3];
  v1[y] = vdata[(indices[i])*3+1] - vdata[(indices[i+y])*3+1];
  v2[y] = vdata[(indices[i])*3+1] - vdata[(indices[i+z])*3+1];
  v1[z] = vdata[(indices[i])*3+2] - vdata[(indices[i+y])*3+2];
  v2[z] = vdata[(indices[i])*3+2] - vdata[(indices[i+z])*3+2];

  // fprintf(stderr,"%f   %f   \n", vdata[(indices[i])*3], vdata[(indices[i+y])*3]);

  tempx = v1[y]*v2[z] - v1[z]*v2[y];
  tempy = -v1[x]*v2[z] + v1[z]*v2[x];
  tempz = v1[x]*v2[y] - v1[y]*v2[x];

  mag = sqrt(tempx*tempx + tempy*tempy + tempz*tempz);
 
  *normals = tempx/mag;
  *(normals+sizeof(GLfloat)) = tempy/mag;
  *(normals+2*sizeof(GLfloat)) = tempz/mag;

  
};

// REMOVE ABOVE

void 
GLPlayer::move(const GLint &x=0, const GLint &y=0, const GLint &z=0){

  // X Speed manipulation

  if(x==1){

    if(m_dXvel < MAXSPEED){
    m_dXvel += ACCEL;
    }

  }

  if(x==0 && m_dXvel > 0){
    m_dXvel -= SLOW;
  }
  else if(x==0 && m_dXvel < 0){
    m_dXvel += SLOW;
  }
  else if(x==0 && m_dXvel == 0){
    m_dXvel = 0;
  }

  if(x==-1){

    if(m_dXvel > -MAXSPEED){
      m_dXvel -= ACCEL;
    }

  }


  // Y Speed manipulation

  if(y==1){

    if(m_dYvel < MAXSPEED){
    m_dYvel += ACCEL;
    }

  }

  if(y==0 && m_dYvel > 0){
    m_dYvel -= SLOW;
  }
  else if(y==0 && m_dYvel < 0){
    m_dYvel += SLOW;
  }
  else if(y==0 && m_dYvel == 0){
    m_dYvel = 0;
  }

  if(y==-1){

    if(m_dYvel > -MAXSPEED){
      m_dYvel -= ACCEL;
    }
  }

  this->tilt(m_dXvel, m_dYvel);
  this->shift(m_dXvel, m_dYvel);


  
}


void 
GLPlayer::setVel(const GLdouble &x, const GLdouble &y){

  m_dXvel = x;
  m_dYvel = y;

}

//============================= Access      ==================================



//============================= Inquiry    ===================================
/////////////////////////////// Protected Methods ////////////////////////////

/////////////////////////////// Private   Methods ////////////////////////////
