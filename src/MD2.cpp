#include <stdio.h>

#include <GL/gl.h>

#include "Math.h"
#include "MD2.h"

MD2::MD2 () {
  
  stateStart = (IDLE1_START); 
  stateEnd = (IDLE1_END);
  numGlCommands = (0); 
  frameSize = (0); 
  numFrames = (0); 
  currentFrame = (IDLE1_START); 
  nextFrame = (currentFrame+1);
  endFrame = (IDLE1_END); 
  interpolation = (0.0f); 
}

MD2::~MD2 () {

  if (glCommands) delete [] glCommands;
  if (frames) delete [] frames;
}

bool MD2::Load (char* filename) {

  FILE* file;
  MD2_HEADER header;

  //Open the .md2 model file
  if ((file = fopen (filename, "rb")) == NULL) {

    fprintf (stderr, "MD2::Load: could not open \"%s\" correctly\n", filename);
    return false;
  }
	
  //Read in the header
  fread (&header, sizeof (MD2_HEADER), 1, file);

  if (header.magic!= 844121161) {

    fprintf (stderr, "MD2::Load: \"%s\" is not a valid .md2 file\n", filename);
    return false;
  }
	
  if (header.version!=8) {

    fprintf (stderr, "MD2::Load: \"%s\" is not a valid .md2 file\n", filename);
    return false;
  }

  //Create space for the frame information
  frames = new char [header.frameSize * header.numFrames];
	
  //Check to see if it allocated correctly
  if (frames == NULL) return false;

  //Zoom to the correct spot in the file
  fseek (file, header.offsetFrames, SEEK_SET);
  fread (frames, header.frameSize*header.numFrames, 1, file);

  //Create space for the GL command information (whether or not to use tri strips, or tri fans)
  glCommands = new long [header.numGlCommands * sizeof (long)];

  //Check to see if it allocated correctly
  if (glCommands == NULL) return false;

  //Zoom to the correct spot in the file
  fseek (file, header.offsetGlCommands, SEEK_SET);
  fread (glCommands, header.numGlCommands * sizeof (long), 1, file);

  //Move the important information from the header, to the permanent class info.
  numFrames = header.numFrames;
  numGlCommands = header.numGlCommands;
  frameSize = header.frameSize;
  numTriangles = header.numTriangles;
  
  //Close 'da friggin file mon
  fclose (file);	
  
  //Lets get outta here
  fprintf (stderr, "MD2::Load: loaded \"%s\" correctly\n", filename);
  return true;
}

//------------------------------------------------------------------//
//- void Render(int) -----------------------------------------------//
//------------------------------------------------------------------//
//- Description: This function renders an .md2 model with the given-//
//-				 frame of animation.		   -//
//------------------------------------------------------------------//
//- Ok, now I really owe Justin a big one for this... His code     -//
//- seems to be the only one that took advantage of the gl commands-//
//- that are within the md2 file (for speed)!			   -//
//------------------------------------------------------------------//

void MD2::Render (int numFrame) {

  static MD2_MODELVERTEX vertList[100];

  MD2_FRAME_PTR	currentFrame;
  VERTEX v1;
  long*	command;
  float	texcoord[2];
  int loop;
  int vertIndex;
  int type;
  int numVertex;
  int index;
  
  //Get the current frame and gl command information
  currentFrame = (MD2_FRAME*)((char*) frames + frameSize * numFrame);
  command = glCommands;
  
  //Make sure that the command doesn't equal 0, and if it doesn't lets start rendering!
  while ((*command)!=0) {

    if (*command>0) { 

      //This is a triangle strip
      numVertex= *command; 
      command++; 
      type= 0;
    }
     
    else {
	 
      //This is a triangle fan
      numVertex= - *command; 
      command++; 
      type= 1;
    }
      
    if (numVertex < 0) numVertex = -numVertex;
      
    index= 0;

    //Fill the vertex list information
    for (loop=0; loop<numVertex; loop++) {

      vertList[index].u = *((float*)command); 
      command++;
      vertList[index].v = *((float*)command); 
      command++;
	  
      vertIndex = *command; 
      command++;
	  
      vertList[index].x = ((currentFrame->vertices[vertIndex].vertex[0] * currentFrame->scale[0]) + currentFrame->translate[0]);
      vertList[index].z = -((currentFrame->vertices[vertIndex].vertex[1] * currentFrame->scale[1]) + currentFrame->translate[1]);
      vertList[index].y = ((currentFrame->vertices[vertIndex].vertex[2] * currentFrame->scale[2]) + currentFrame->translate[2]);
      index++;
    }
      
    //If the .md2 was optimized for use with triangle strips...
    if (type==0) {

      glBegin (GL_TRIANGLE_STRIP);
	
      for (loop=0; loop<index; loop++) {
	
	v1.vertex[0] = (vertList[loop].x);
	v1.vertex[1] = (vertList[loop].y);
	v1.vertex[2] = (vertList[loop].z);
	      
	texcoord[0]= vertList[loop].u;
	texcoord[1]= vertList[loop].v;
	      
	glTexCoord2fv (texcoord);
	glVertex3fv (v1.vertex);
      }

      glEnd();
    }
      
    //If the .md2 was made for use with triangle fans...
    else {

      glBegin(GL_TRIANGLE_FAN);
	
      for(loop = 0; loop < index; loop++) {

	v1.vertex[0] = (vertList[loop].x);
	v1.vertex[1] = (vertList[loop].y);
	v1.vertex[2] = (vertList[loop].z);
	      
	texcoord[0] = vertList[loop].u;
	texcoord[1] = vertList[loop].v;
	      
	glTexCoord2fv (texcoord);
	v1.SendToOGL ();
      }

      glEnd();
    }
  }
}

//------------------------------------------------------------------//
//- void Animate(int, int, float) ----------------------------------//
//------------------------------------------------------------------//
//- Description: This function animates a model from the start     -//
//-				 frame, to the end frame, with the speed that you  -//
//-				 give (in percent).								   -//
//------------------------------------------------------------------//
//- I got the idea for this one from Dave Astle and Kevin Hawkins  -//
//- (two really cool guys), but I had to implement the code in it  -//
//- myself!														   -//
//------------------------------------------------------------------//

void MD2::Animate (int startFrame, int EndFrame, float percent) {

  //Check to see if the current frame equals -1 (which means there was a 
  //sudden change of states)
  if (currentFrame == -1 || currentFrame > endFrame) {

    currentFrame = startFrame;
    nextFrame = currentFrame+1;
    endFrame = EndFrame;
  }
  
  //If the interpolation value is above one, then we advance to the next frame
  //of animation for the model
  if (interpolation > 1.0f) {

    interpolation = 0.0f;
    currentFrame = nextFrame;
    nextFrame = currentFrame + 1;
  }
  
  interpolation += percent;
  Render (currentFrame);
}

//------------------------------------------------------------------//
//- void SetState(int) ---------------------------------------------//
//------------------------------------------------------------------//
//- Description: This sets the models state from one of the		   -//
//-				 predefined constants, the state will start		   -//
//-				 animating on the next frame (as long as you are   -//
//-				 using the Animate(...) function).				   -//
//------------------------------------------------------------------//
//- Ok, this one was all my idea, so no one to thank!!! HAHAHA! Ok -//
//- sorry, a little too much Mountain Dew for me! :P			   -//
//------------------------------------------------------------------//

void MD2::SetState (int state) {
	
  switch(state) {

  case IDLE1:
    stateStart = IDLE1_START;
    stateEnd = IDLE1_END;
    currentFrame =-1;
    break;

  case RUN:
    stateStart = RUN_START;
    stateEnd = RUN_END;
    currentFrame =-1;
    break;

  case SHOT_STAND:
    stateStart = SHOT_STAND_START;
    stateEnd = SHOT_STAND_END;
    currentFrame =-1;
    break;

  case SHOT_SHOULDER:
    stateStart = SHOT_SHOULDER_START;
    stateEnd = SHOT_SHOULDER_END;
    currentFrame =-1;
    break;

  case JUMP:
    stateStart = JUMP_START;
    stateEnd = JUMP_END;
    currentFrame =-1;
    break;

  case IDLE2:
    stateStart = IDLE2_START;
    stateEnd = IDLE2_END;
    currentFrame =-1;
    break;

  case SHOT_FALLDOWN:
    stateStart = SHOT_FALLDOWN_START;
    stateEnd = SHOT_FALLDOWN_END;
    currentFrame =-1;
    break;

  case IDLE3:
    stateStart = IDLE3_START;
    stateEnd = IDLE3_END;
    currentFrame =-1;
    break;

  case IDLE4:
    stateStart = IDLE4_START;
    stateEnd = IDLE4_END;
    currentFrame =-1;
    break;

  case CROUCH:
    stateStart = CROUCH_START;
    stateEnd = CROUCH_END;
    currentFrame =-1;
    break;

  case CROUCH_CRAWL:
    stateStart = CROUCH_CRAWL_START;
    stateEnd = CROUCH_CRAWL_END;
    currentFrame =-1;
    break;

  case CROUCH_IDLE:
    stateStart = CROUCH_IDLE_START;
    stateEnd = CROUCH_IDLE_END;
    currentFrame =-1;
    break;

  case CROUCH_DEATH:
    stateStart = CROUCH_DEATH_START;
    stateEnd = CROUCH_DEATH_END;
    currentFrame =-1;
    break;

  case DEATH_FALLBACK:
    stateStart = DEATH_FALLBACK_START;
    stateEnd = DEATH_FALLBACK_END;
    currentFrame =-1;
    break;

  case DEATH_FALLFORWARD:
    stateStart = DEATH_FALLFORWARD_START;
    stateEnd = DEATH_FALLFORWARD_END;
    currentFrame =-1;
    break;

  case DEATH_FALLBACKSLOW:
    stateStart = DEATH_FALLBACKSLOW_START;
    stateEnd = DEATH_FALLBACKSLOW_END;
    currentFrame =-1;
    break;
  }	
}
