//////////////////////////////////////////////////////////////////////////
// Name: BSM 
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
#include "BSM.h"                                // class implemented
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <GL/gl.h>
#include <GL/glu.h>

#define MAXDIG 5

/////////////////////////////// Public ///////////////////////////////////////

//============================= Lifecycle ====================================

BSM::BSM()
{
}// BSM

BSM::BSM(const BSM&)
{
}// BSM

BSM::~BSM()
{
}// ~BSM


//============================= Operators ====================================

BSM& 
BSM::operator=(const BSM&rhs)
{
   if ( this==&rhs ) {
        return *this;
    }
    //superclass::operator =(rhs);

    //add local assignments

    return *this;

}// =

GLvoid 
BSM::FindNormal( GLuint i, GLfloat *normals){

  GLuint x=0;
  GLuint y=1;
  GLuint z=2;
  GLfloat v1[3],v2[3];
  GLfloat mag, tempx, tempy, tempz;

  v1[x] = m_ptrVertex[(m_ptrPoints[i])*3] - m_ptrVertex[(m_ptrPoints[i+y])*3];
  v2[x] = m_ptrVertex[(m_ptrPoints[i])*3] - m_ptrVertex[(m_ptrPoints[i+z])*3];
  v1[y] = m_ptrVertex[(m_ptrPoints[i])*3+1] - m_ptrVertex[(m_ptrPoints[i+y])*3+1];
  v2[y] = m_ptrVertex[(m_ptrPoints[i])*3+1] - m_ptrVertex[(m_ptrPoints[i+z])*3+1];
  v1[z] = m_ptrVertex[(m_ptrPoints[i])*3+2] - m_ptrVertex[(m_ptrPoints[i+y])*3+2];
  v2[z] = m_ptrVertex[(m_ptrPoints[i])*3+2] - m_ptrVertex[(m_ptrPoints[i+z])*3+2];

  // fprintf(stderr,"%f   %f   \n", m_ptrVertex[(indices[i])*3], m_ptrVertex[(indices[i+y])*3]);

  tempx = v1[y]*v2[z] - v1[z]*v2[y];
  tempy = -v1[x]*v2[z] + v1[z]*v2[x];
  tempz = v1[x]*v2[y] - v1[y]*v2[x];

  mag = sqrt(tempx*tempx + tempy*tempy + tempz*tempz);

  *normals = tempx/mag;
  *(normals+sizeof(GLfloat)) = tempy/mag;
  *(normals+2*sizeof(GLfloat)) = tempz/mag;


}


void 
BSM::draw(){


  GLfloat normal[3];
  GLfloat *ntemp = new GLfloat[3];

  glColor3f(0.5f, 0.5f, 0.5f);

  glBegin(GL_TRIANGLES);
  for (unsigned i=0; i<m_ptrPoints.size(); i=i+3){


    FindNormal(i, ntemp);
    normal[0] = *ntemp;
    normal[1] = *(ntemp + sizeof(GLfloat));
    normal[2] = *(ntemp + 2*sizeof(GLfloat));
    glNormal3fv(normal);

    glVertex3fv(&m_ptrVertex[(m_ptrPoints[i+0]-1)*3]);
    glVertex3fv(&m_ptrVertex[(m_ptrPoints[i+1]-1)*3]);
    glVertex3fv(&m_ptrVertex[(m_ptrPoints[i+2]-1)*3]);

  }
  glEnd();
  
  delete ntemp;

}

bool 
BSM::LoadBSM(char *filename){

  double dTemp;
  char *cTemp = new char[MAXDIG];
  int counter;
  ifstream file(filename);
  if(!file){
    cout << "Unable to open file" << endl;
    return false;
  }
  
    while(file.peek() == '#'){
  
      file.getline(cTemp, MAXDIG);

  }

  while(file.get() != '<' ){
  }


  while( file.get() != '>'){

    if(file.peek() != ' ' && file.peek() != '\n' && file.peek() != '>' ){
      for(int i=0; i < MAXDIG; i++){
	cTemp[i]=' ';
      }
      cTemp[MAXDIG-1]='\0';
      counter = 0;
      while(file.peek() != ',' && file.peek() != '>' && counter < MAXDIG){
	cTemp[counter] = file.get();
	counter++;
      }

      dTemp = atof(cTemp);
      cout << dTemp << " ";  
       m_ptrVertex.push_back(dTemp);
      
    }
  }  

  cout << "\n" << endl;

  while(file.get() != '[' ){
  }

  while( file.get() != ']'){

    if(file.peek() != ' ' && file.peek() != '\n' && file.peek() != ']' ){
      for(int i=0; i < MAXDIG; i++){
	cTemp[i]=' ';
      }

      cTemp[MAXDIG-1]='\0';
      counter = 0;

      while(file.peek() != ',' && file.peek() != ']' && counter < MAXDIG){
	cTemp[counter] = file.get();
	counter++;
      }

      dTemp = atoi(cTemp);
      cout << dTemp << " "; 
      m_ptrPoints.push_back(dTemp);
    }


 
  }

  cout << endl;
  file.close();
  delete cTemp;
  return true;
  
}



// //============================= Operations ===================================
// //============================= Access      ==================================
// //============================= Inquiry    ===================================
// /////////////////////////////// Protected Methods ////////////////////////////

// /////////////////////////////// Private   Methods ////////////////////////////
