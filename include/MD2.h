/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: t; c-basic-offset: 3 -*- */
#ifndef MD2_H
#define MD2_H

/* MD2 constants */
#define MAX_TRIANGLES 4096
#define MAX_VERTICES  2048
#define MAX_TEXCOORDS 2048
#define MAX_FRAMES    512

#define CHUNK1 0
#define CHUNK2 1
#define CHUNK3 2
#define CHUNK4 3

/* MD2 state constants */
#define ANIMATE_CURRENT -100

#define IDLE1		           0
#define RUN		           1
#define SHOT_STAND	           2
#define SHOT_SHOULDER	           3
#define JUMP		           4
#define IDLE2		           5
#define SHOT_FALLDOWN	           6
#define IDLE3		           7
#define IDLE4		           8
#define CROUCH		           9
#define CROUCH_CRAWL	          10
#define CROUCH_IDLE	          11
#define CROUCH_DEATH		  12
#define DEATH_FALLBACK		  13
#define DEATH_FALLFORWARD	  14
#define DEATH_FALLBACKSLOW	  15

#define IDLE1_START		   0
#define IDLE1_END		  39
#define RUN_START		  40
#define RUN_END			  45
#define SHOT_STAND_START	  46
#define SHOT_STAND_END		  60
#define SHOT_SHOULDER_START	  61
#define SHOT_SHOULDER_END	  66
#define JUMP_START		  67
#define JUMP_END		  73
#define IDLE2_START		  74
#define IDLE2_END		  95
#define SHOT_FALLDOWN_START	  96
#define SHOT_FALLDOWN_END	 112
#define IDLE3_START		 113
#define IDLE3_END		 122
#define IDLE4_START		 123
#define IDLE4_END		 135
#define CROUCH_START		 136
#define CROUCH_END		 154
#define CROUCH_CRAWL_START	 155
#define CROUCH_CRAWL_END	 161
#define CROUCH_IDLE_START	 162
#define CROUCH_IDLE_END		 169
#define CROUCH_DEATH_START	 170
#define CROUCH_DEATH_END	 177
#define DEATH_FALLBACK_START	 178
#define DEATH_FALLBACK_END	 185
#define DEATH_FALLFORWARD_START	 186
#define DEATH_FALLFORWARD_END	 190
#define DEATH_FALLBACKSLOW_START 191
#define DEATH_FALLBACKSLOW_END	 198

//------------------------------------------------------------------//
//- MD2 STRUCTURES -------------------------------------------------//
//------------------------------------------------------------------//
typedef struct MD2_HEADER_TYP {
  
  int magic;				//The 'magic' number (always 844121161)
  int version;			//The version number of the file (always 8)
  int skinWidth;			//The width of the model's skin
  int skinHeight;			//The height of the model's skin
  int frameSize;			//The size of each frame (in BYTEs)
  int numSkins;			//The model's number of skins
  int numVertices;		//The model's number of vertices
  int numTexcoords;		//The model's number of texture coordinates (most likely, its not the same number as the vertices)
  int numTriangles;		//The number of triangles that make up the model
  int numGlCommands;		//The number of DWORDs (4 bytes) in the GLcommand list (which decide to render the model with tri strips, or fans)
  int numFrames;			//The number of frames (of animation) that the model has
  int offsetSkins;		//Offset in the file of the model, to where the skin information is
  int offsetTexcoords;	//Offset in the file of the model, to where the texture coordinate information is
  int offsetTriangles;	//Offset in the file of the model, to where the traingle information is
  int offsetFrames;		//Offset in the file of the model, to where the first frame information is given
  int offsetGlCommands;	//Offset in the file of the model, to where the GLcommand information is
  int offsetEnd;			//Offset in the file of the model, to where the end of it is
	
} MD2_HEADER, *MD2_HEADER_PTR;

typedef struct MD2_VERTEX_TYP {

  unsigned char vertex[3];		//Scaled version of the model's 'real' vertex coordinate
  unsigned char lightNormalIndex;	//An index into the table of normals, kept by Quake 2
	
} MD2_VERTEX, *MD2_VERTEX_PTR;

typedef struct MD2_FRAME_TYP {

  float	   scale[3];		//The scale used by the model's 'fake' vertex structure
  float	   translate[3];	//The translation used by the model's 'fake' vertex structure
  char	   name[16];		//The name for the frame
  MD2_VERTEX vertices[1];		//An array of MD2_VERTEX structures

} MD2_FRAME, *MD2_FRAME_PTR;

typedef struct MD2_MODELVERTEX_TYP {

  float x,y,z;				//The (x,y,z) location of the vertex
  float u,v;					//The (u,v) location of the texture coordinate

} MD2_MODELVERTEX, *MD2_MODELVERTEX_PTR;


//------------------------------------------------------------------//
//- class MD2 ------------------------------------------------------//
//------------------------------------------------------------------//
//- A class for the Quake 2 model mesh (includes key frames for    -//
//- animation).													   -//
//------------------------------------------------------------------//

class MD2 {
  
 private:	

  int numGlCommands;
  long* glCommands;

  int numTriangles;

 public:

  int stateStart;
  int stateEnd;

  int frameSize;
  int numFrames;
  char* frames;

  int currentFrame;
  int nextFrame;
  int endFrame;
  float interpolation;
	
  bool Load (char* filename);
  void Render (int numFrame);
  void Animate (int startFrame, int EndFrame, float Interpolation);
  void SetState (int state);

  //  MD2 (int,int,int,int,int,int,int,int,float);
  MD2 ();
  ~MD2 ();
  
};

#endif
