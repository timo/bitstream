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

#define MAXDIG 5

/////////////////////////////// Public ///////////////////////////////////////

//============================= Lifecycle ====================================

BSM::BSM()
  :m_ptrVertex(NULL),
   m_ptrPoints(NULL),
   m_uVSize(0),
   m_uPSize(0)
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



void 
BSM::draw(){

  cout << "Nothing Yet." << endl;

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
  
  //  while(myFile.peek() == '#'){
  //
  // }

  while(file.get() != '<' ){
  }


  while( file.get() != '>'){

    if(file.peek() != ' ' && file.peek() != '\n' && file.peek() != '>' ){
      for(int i=0; i < MAXDIG; i++){
	cTemp[i]=0;
      }
      counter = MAXDIG-1;
      while(file.peek() != ',' && counter >= 0){
	cTemp[counter] = file.get();
       	cout << counter << endl;
	counter--;
      }

      dTemp = atof(cTemp);
      cout << dTemp << endl;  
      addVertex(dTemp);

    }
  }  

  cout << "First Part" << endl;

  while(file.get() != '[' ){
  }

  while( file.get() != ']' || !file.eof()){

    if(file.peek() != ' ' && file.peek() != '\n'){

    file.get(cTemp, 5, ',');

    dTemp = atof(cTemp);

      cout << dTemp << endl;  
      addPoint(dTemp);
    }
  }  

  file.close();

  return true;
  
}



void 
BSM::addVertex(const double &vertex){

  if(resize(m_uVSize+1, 0, m_uVSize)){    // Make sure we get memory
    cout << "memory allocation failed, the number: "<< vertex
	 << "was not inserted into the set" << endl;       
  }
  
  else{
    m_ptrVertex[m_uVSize-1]=vertex;         // If it is, set it
  }

}

void 
BSM::addPoint(const double &point){

  if(resize(m_uPSize+1, 1 , m_uPSize)){    // Make sure we get memory
    cout << "memory allocation failed, the number: "<< point
	 << "was not inserted into the set" << endl;       
  }
  
  else{
    m_ptrPoints[m_uPSize-1]=point;         // If it is, set it
  }

}



int
BSM::resize(const unsigned &Uns, const unsigned &flag, unsigned &counter){

  unsigned place=0;
  double *tmpPointer = new double[Uns];

  if(!tmpPointer){
    return 1; //Allocation failed!
  }

  if(flag==0){
    if(Uns == 0) {         //See if it is resize to zero or 
      if(m_ptrVertex){
	delete [] m_ptrVertex;
      }
      m_ptrVertex = NULL;
      counter = Uns;

    }

    for(unsigned i=0; i<Uns; i++){   //Constructor sets all values to 0
      tmpPointer[i]=0;
    }

    if(counter < Uns){
      while(place < counter){

	tmpPointer[place] = m_ptrVertex[place];

	place++;

      }
    }

    place = 0;

    if(counter >= Uns){
      while(place < Uns){
	tmpPointer[place] = m_ptrVertex[place];

	place++;
      }
    }


    if(m_ptrVertex){
      delete [] m_ptrVertex;
    }

    m_ptrVertex = tmpPointer;
  }


  if(flag==1){

    if(Uns == 0) {         //See if it is resize to zero or 
      if(m_ptrPoints){
	delete [] m_ptrPoints;
      }
      m_ptrPoints = NULL;
      counter = Uns;

    }

    for(unsigned i=0; i<Uns; i++){   //Constructor sets all values to 0
      tmpPointer[i]=0;
    }

    if(counter < Uns){
      while(place < counter){

	tmpPointer[place] = m_ptrPoints[place];

	place++;

      }
    }

    place = 0;

    if(counter >= Uns){
      while(place < Uns){
	tmpPointer[place] = m_ptrPoints[place];

	place++;
      }
    }


    if(m_ptrPoints){
      delete [] m_ptrPoints;
    }

    m_ptrPoints = tmpPointer;

  }

  counter = Uns;

  return 0;

}

unsigned
BSM::size()const
{

  return m_uVSize;

}

//============================= Operations ===================================
//============================= Access      ==================================
//============================= Inquiry    ===================================
/////////////////////////////// Protected Methods ////////////////////////////

/////////////////////////////// Private   Methods ////////////////////////////
