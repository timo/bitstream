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
#include <math.h>

#define MAXDIG 5
#define COMMENT 150
/////////////////////////////// Public ///////////////////////////////////////

//============================= Lifecycle ====================================

BSM::BSM()
  :m_mainDamage(100),
   foundnormals(0)
{
  cout << "In BSM Constructor" << endl;
  foundnormals = 0;
}// BSM

BSM::BSM(const BSM&)
  :m_mainDamage(100),
   foundnormals(0)
{
  cout << "In BSM Copy Constructor" << endl;
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
  cout << "In BSM Assignment Operator" << endl;
    //add local assignments
   foundnormals=false;
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

  for(unsigned j=0; j<m_vBSM.size(); j++){
    
    m_ptrPoints = *(m_vBSM[j].get_vec());

    if(m_vBSM[j].isAlive()){


      //Normal calculations, only runs on first draw
      if(foundnormals != 1){

	m_normals.resize(m_ptrPoints.size()+1);
	GLfloat *ntemp = new GLfloat[3];
	
	for (unsigned i=0; i<m_ptrPoints.size(); i=i+3){	  
	  FindNormal(i, ntemp);
	  m_normals[i+0] = *ntemp;
	  m_normals[i+1] = *(ntemp + sizeof(GLfloat));
	  m_normals[i+2] = *(ntemp + 2*sizeof(GLfloat));
	}

	foundnormals = 1;
	delete ntemp;
      }


      glBegin(GL_TRIANGLES);
      for (unsigned i=0; i<m_ptrPoints.size(); i=i+3){
	
	glNormal3fv(&m_normals[i]);
	  
	glVertex3fv(&m_ptrVertex[(m_ptrPoints[i+0]-1)*3]);
	glVertex3fv(&m_ptrVertex[(m_ptrPoints[i+1]-1)*3]);
	glVertex3fv(&m_ptrVertex[(m_ptrPoints[i+2]-1)*3]);
	
      }
      glEnd();
    }

  }
}


void 
BSM::hit(const int &region){

  if(region == 0){
    m_mainDamage-=5;
  }

  else{
    m_mainDamage-=2;
    m_vBSM[region].hit();
  }

}

bool 
BSM::isAlive(const int &region)const{

  return m_vBSM[region].isAlive();

}

unsigned
BSM::size()const{

  return m_vBSM.size();

}


  
  bool 
BSM::LoadBSM(char *filename){

    double dTemp;
    char *cTemp = new char[MAXDIG];
    char *comment = new char[COMMENT];
    int counter;

    BSMPiece tempPiece;

    ifstream file(filename);
    if(!file){
      cout << "Unable to open file" << endl;
      return false;
    }
  
    while(file.peek() == '#'){
      
      file.getline(comment, COMMENT);
      
      // cout << comment << endl;
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
	m_ptrVertex.push_back(dTemp);
	
      }
    }  
    
    cout << "\n" << endl;
    
    int iTemp;
    
    while( !file.eof()){

      if(file.get() == '['){
	
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
	    
	    iTemp = atoi(cTemp);

 	    tempPiece.addVertex(iTemp);
	  } 
	}

	m_vBSM.push_back(tempPiece) ;

      }
      tempPiece.clear_vec();  
    }
    

    file.close();

    delete cTemp;
    delete comment;

    return true;
  
  }

GLdouble 
BSM::getDamage(){

  return m_mainDamage;

}
// //============================= Operations ===================================
// //============================= Access      ==================================
// //============================= Inquiry    ===================================
// /////////////////////////////// Protected Methods ////////////////////////////

// /////////////////////////////// Private   Methods ////////////////////////////
