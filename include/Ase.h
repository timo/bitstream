/*==========================================================================
 * 
 * Project : Freyja
 * Author  : Terry 'Mongoose' Hendrix II
 * Website : http://gooseegg.sourceforge.net
 * Email   : stu7440@westga.edu
 * Object  : Ase
 * Comments: This is the ASE model class.
 *
 *           See file COPYING for license details.
 *
 *
 *
 *-- Test Defines -----------------------------------------------------
 *           
 * TEST_ASE - Builds Ase with it's test code as a console program 
 *
 *-- History ---------------------------------------------------------- 
 *
 * 2000-10-15:
 * Mongoose - Created, ASE specs provided by nate miller
 ==========================================================================*/


#ifndef __FREYJA_MONGOOSE_ASE_H
#define __FREYJA_MONGOOSE_ASE_H

#define NUM_VERTEX			"*MESH_NUMVERTEX"
#define NUM_FACES			"*MESH_NUMFACES"
#define NUM_TVERTEX			"*MESH_NUMTVERTEX"
#define NUM_TFACES			"*MESH_NUMTVFACES"
#define VERTEX_LIST			"*MESH_VERTEX_LIST"
#define VERTEX				"*MESH_VERTEX"
#define FACE_LIST			"*MESH_FACE_LIST"
#define FACE				"*MESH_FACE"
#define NORMALS				"*MESH_NORMALS"
#define FACE_NORMAL			"*MESH_FACENORMAL"
#define NVERTEX				"*MESH_VERTEXNORMAL"
#define TVERTEX				"*MESH_TVERT"
#define TFACE				"*MESH_TFACE"
#define TEXTURE				"*BITMAP"
#define UTILE				"*UVW_U_TILING"
#define VTILE				"*UVW_V_TILING"
#define UOFFSET				"*UVW_U_OFFSET"
#define VOFFSET				"*UVW_V_OFFSET"

#ifndef vec_t
typedef float vec_t;
#endif

#ifndef vec2_t
typedef vec_t vec2_t[2];
#endif

#ifndef vec3_t
typedef vec_t vec3_t[3];
#endif

typedef struct
{
  int vertIndex[3];  // indicies for the verts that make up this triangle
  int coordIndex[3]; // indicies for the tex coords to texture this face
  vec3_t normal;     // face normal
} ase_triangle_t;


typedef struct 
{
  char texName[255]; // texture name
  int texId;         // texture id
  vec_t uTile;       // u tiling of texture
  vec_t vTile;       // v tiling of texture
  vec_t uOffset;     // u offset of texture
  vec_t vOffset;     // v offset of texture
} ase_texture_t;


typedef struct
{
  int numVertex;     // number of verts in the model
  int numFaces;      // number of faces in the model
  int numTexFaces;   // number of textured faces in model
  int numTexVertex;  // number of texture coords
  int normals;       // do we have normal information?  
  vec3_t *verts;     // model verts
  vec2_t *texVerts;  // texture coords
  vec3_t *vertNorms; // vertex normals 
  ase_triangle_t *faces; // faces of model
  ase_texture_t texture; // texture information
} ase_model_t;


class Ase
{
 public:
  
  Ase();
  /*--------------------------------------------
   * Created  : 2000-10-15 by Mongoose
   * Modified : 
   *
   * Pre  : None
   * Post : Ase object is constructed
   --------------------------------------------*/

  ~Ase();
  /*--------------------------------------------
   * Created  : 2000-10-15 by Mongoose
   * Modified : 
   *
   * Pre  : Ase object is allocated
   * Post : Ase object is deconstructed
   --------------------------------------------*/  

  void Clear();
  /*--------------------------------------------
   * Created  : 2000-10-15 by Mongoose
   * Modified : 
   *
   * Pre  : 
   * Post : Clears data in this agent
   --------------------------------------------*/

  ase_model_t *Model();
  /*--------------------------------------------
   * Created  : 2000-10-15 by Mongoose
   * Modified : 
   *
   * Pre  : 
   * Post : Returns model data
   --------------------------------------------*/
  
  void Model(ase_model_t *model);
  /*--------------------------------------------
   * Created  : 2000-10-15 by Mongoose
   * Modified : 
   *
   * Pre  : model is valid ase model
   * Post : Sets model data
   *
   *        This is a hack until I get
   *        the class ready for a new interface
   --------------------------------------------*/

  int Load(char *filename);
  /*--------------------------------------------
   * Created  : 2000-10-15 by Mongoose
   * Modified : 
   *
   * Pre  : 
   * Post : Load ASE format file
   --------------------------------------------*/  

  int Save(char *filename);
  /*--------------------------------------------
   * Created  : 2000-10-15 by Mongoose
   * Modified : 
   *
   * Pre  : 
   * Post : Save ASE format file
   --------------------------------------------*/ 

 private:

  ase_model_t *NewModel();
  /*--------------------------------------------
   * Created  : 2000-10-15 by Mongoose
   * Modified : 
   *
   * Pre  : 
   * Post : Makes a new initizlied ase_model_t
   --------------------------------------------*/


  ase_model_t *_model;              /* The model data */
};


#endif

