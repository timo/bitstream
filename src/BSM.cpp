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
#include <ctype.h>	// for isdigit()

#define MAXDIG 5
#define COMMENT 150
/////////////////////////////// Public ///////////////////////////////////////

//============================= Lifecycle ====================================

BSM::BSM()
  :m_mainDamage(100)
{
  cout << "In BSM Constructor" << endl;
}// BSM

BSM::BSM(const BSM&)
  :m_mainDamage(100)
{
  cout << "In BSM Copy Constructor" << endl;
}// BSM

BSM::~BSM()
{
  delete [] m_ptrVertex;	
  delete [] m_ptrNormal;	
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
   return *this;

}

void 
BSM::draw(){

  glVertexPointer(3,GL_FLOAT,0,m_ptrVertex);
  glNormalPointer(GL_FLOAT,0,m_ptrNormal);

  for(unsigned j=0; j<m_vBSM.size(); j++){
    
    m_ptrPoints = *(m_vBSM[j].get_vec());

    if(m_vBSM[j].isAlive()){
      glBegin(GL_TRIANGLES);
      for (unsigned i=0; i<m_ptrPoints.size(); i++){
        glArrayElement(m_ptrPoints[i]-1);
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
    int vertices;

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

    {
      // Burn newlines so they don't burn you
      while (file.peek() == '\n') file.get ();  
      file.getline(cTemp, MAXDIG);
      vertices = atoi(cTemp);
      m_ptrVertex = new GLfloat[vertices*3];
      m_ptrNormal = new GLfloat[vertices*3];
      for (int k=0; k < vertices*3; k++){
	m_ptrVertex[k] = 0.0;
	m_ptrNormal[k] = 0.0;
      }
    }
    
    int j=0;
    while( file.get() != '>' && j < vertices*3){
      
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
	m_ptrVertex[j++]=dTemp;
      }
    }  
    
    j=0;
    while( file.get() != '}' && j < vertices*3){
      
      if(file.peek() != ' ' && file.peek() != '\n' && file.peek() != '}' ){
	for(int i=0; i < MAXDIG; i++){
	  cTemp[i]=' ';
	}
	cTemp[MAXDIG-1]='\0';
	counter = 0;
	while(file.peek() != ',' && file.peek() != '}' && counter < MAXDIG){
	  cTemp[counter] = file.get();
	  counter++;
	}
	
	dTemp = atof(cTemp); 
	m_ptrNormal[j++]=dTemp;
      }
    }

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

    // Setup the vertex array
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

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
