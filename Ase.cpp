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
 *           This code is based on nate's ASE demo.
 *           under non commerical lisence - I will improve this.
 *           Just give me some time to add support.  =)
 *
 *           Nate - backport my fixes, you had some incorrect code, but
 *           thanks for the ASE format.  ;)           
 *
 *-- Test Defines -----------------------------------------------------
 *           
 * TEST_ASE   - Builds Ase with it's test code as a console program 
 *
 *-- History ---------------------------------------------------------- 
 *
 * 2000-10-15:
 * Mongoose - Created, ASE specs provided by nate miller
 ==========================================================================*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Ase.h"


void aseGetInfo (FILE *s, ase_model_t *p)
{
  char data[255];

  rewind (s);

  while (!feof (s))
  {
    fscanf(s, "%s", data);
    
    if (!strcmp (data, NUM_VERTEX))
      fscanf(s, "%d", &p->numVertex);
    else if (!strcmp (data, NUM_FACES))
      fscanf(s, "%d", &p->numFaces);
    else if (!strcmp (data, NUM_TVERTEX))
      fscanf(s, "%d", &p->numTexVertex);
    else if (!strcmp (data, NUM_TFACES))
      fscanf(s, "%d", &p->numTexFaces);
    else if (!strcmp (data, NORMALS))
      p->normals = 1;
    else 
      fgets(data, sizeof (data), s);
  }	
}


void aseGetVertex (FILE *s, ase_model_t *p)
{
  int index;

  fscanf (s, "%d", &index);
  // swap y and z cause 3dsm and freyja likes too
  fscanf (s, "%f %f %f", 
	  &p->verts[index][0], 
	  &p->verts[index][2],
	  &p->verts[index][1]);
	
  // in 3dsm negative z goes out of the screen, we want it to go in
  p->verts[index][2] = -p->verts[index][2];
}


void aseGetTVertex (FILE *s, ase_model_t *p)
{
  int index;

  // we ignore the z value
  fscanf (s, "%d", &index);
  fscanf (s, "%f %f", &p->texVerts[index][0], &p->texVerts[index][1]);

#ifdef DEBUG_ASE_TEXEL 
  printf("ASE texel:: %f, %f -> %f, %f\n",
	 p->texVerts[index][0], p->texVerts[index][1],
	 p->texVerts[index][0] * p->texture.uTile, 
	 p->texVerts[index][1] * p->texture.vTile);
#endif

  // Mongoose: Ah, don't make it clamp to 0.0, 0.0   =)
  if (p->texture.uTile)
    p->texVerts[index][0] *= p->texture.uTile;

  if (p->texture.vTile)
    p->texVerts[index][1] *= p->texture.vTile;
}


void aseGetNVertex (FILE *s, ase_model_t *p)
{
  int index;

  fscanf (s, "%d", &index);
  fscanf (s, "%f %f %f", 
	  &p->vertNorms[index][0], 
	  &p->vertNorms[index][2],
	  &p->vertNorms[index][1]); 

  p->vertNorms[index][2] = -p->vertNorms[index][2];
}


void aseGetFaceNormal (FILE *s, ase_model_t *p)
{
  int index;

  fscanf (s, "%d", &index);
  fscanf (s, "%f %f %f", 
	  &p->faces[index].normal[0], 
	  &p->faces[index].normal[2],
	  &p->faces[index].normal[1]); 

  p->faces[index].normal[2] = -p->faces[index].normal[2];
}


void aseGetFace (FILE *s, ase_model_t *p)
{
  int index;

  fscanf (s, "%d:", &index);

  fscanf (s, "\tA:\t%d B:\t%d C:\t%d", 
	  &p->faces[index].vertIndex[0], 
	  &p->faces[index].vertIndex[1], 
	  &p->faces[index].vertIndex[2]); 
}


void aseGetTFace (FILE *s, ase_model_t *p)
{
  int index;

  fscanf (s, "%d:", &index);

  fscanf (s, "%d %d %d", 
	  &p->faces[index].coordIndex[0], 
	  &p->faces[index].coordIndex[1], 
	  &p->faces[index].coordIndex[2]); 
}


void aseGetTextureName(FILE *f, ase_model_t *p)
{
  fscanf(f, " \"%s", p->texture.texName);
	
  p->texture.texName[strlen (p->texture.texName) - 1] = '\0';
}


vec_t aseGetFloatVal(FILE *f)
{
  vec_t v;


  fscanf(f, " %f", &v);

  return v;
}


void aseGetData (FILE *s, ase_model_t *p)
{
  char data[255];

  rewind (s);

  while (!feof (s))
    {
      fscanf (s, "%s", data);

      if (!strcmp (data, VERTEX))
	aseGetVertex (s, p);
      else if (!strcmp (data, TVERTEX))
	aseGetTVertex (s, p);
      else if (!strcmp (data, NVERTEX))
	aseGetNVertex (s, p);
      else if (!strcmp (data, FACE_NORMAL))
	aseGetFaceNormal (s, p);
      else if (!strcmp (data, FACE))
	aseGetFace (s, p);
      else if (!strcmp (data, TFACE))
	aseGetTFace (s, p);
      else if (!strcmp (data, TEXTURE))
	aseGetTextureName (s, p);
      else if (!strcmp (data, UTILE))
	p->texture.uTile = aseGetFloatVal (s);
      else if (!strcmp (data, VTILE))
	p->texture.vTile = aseGetFloatVal (s);
      else if (!strcmp (data, UOFFSET))
	p->texture.uOffset = aseGetFloatVal (s);
      else if (!strcmp (data, VOFFSET))
	p->texture.vOffset = aseGetFloatVal (s);
      else fgets (data, sizeof (data), s);
    }
}


void aseAllocate(ase_model_t *p)
{
  p->verts = new vec3_t[p->numVertex];
  p->faces = new ase_triangle_t[p->numFaces];

  if (p->numTexVertex)
    p->texVerts = new vec2_t[p->numTexVertex];

  if (p->normals)
    p->vertNorms = new vec3_t[p->numVertex];
}


void aseLoadTexture (ase_model_t *p)
{
  static int texIds = 1;

  /*
  if (p->texture.texName[0] != '\0')
    loadTGA (p->texture.texName, texIds);
  */

  p->texture.texId = texIds;
  texIds++;
}


void aseDumpInfo (ase_model_t *p)
{
  printf ("# Model Info\n");
  printf ("# ------------------------------\n");
  printf ("# Num Vertices %d\n", p->numVertex);
  printf ("# Num Tex Vertices %d\n", p->numTexVertex);
  printf ("# Num Faces %d\n", p->numFaces);
  printf ("# Num Tex Faces %d\n", p->numTexFaces);
  printf ("# Model has normals : %s\n", (p->normals) ? "Yes" : "No");
  printf ("# Texture Name : %s\n", 
	  (p->texture.texName[0] != '\0') ? p->texture.texName : "None");
}


//////////////////////////////////////////////////////////////////////////

Ase::Ase()
{
  _model = NULL;
}


Ase::~Ase()
{
  Clear();
}


void Ase::Clear()
{
  if (_model)
  {
    if (_model->verts)
      delete [] _model->verts;

    if (_model->faces)
      delete [] _model->faces;

    if (_model->texVerts)
      delete [] _model->texVerts;

    if (_model->vertNorms)
      delete [] _model->vertNorms;

    delete _model;
  }
}


ase_model_t *Ase::Model()
{
  return _model;
}


void Ase::Model(ase_model_t *model)
{
  Clear();
  _model = model;
}


int Ase::Load(char *filename)
{
  FILE *f;
  
	
  f = fopen(filename, "r");

  if (!f)
  {
    printf("Ase::Load> ERROR file '%s' not found\n", filename);
    return -1;
  }

  Clear();

  _model = NewModel();

  if (!_model)
    return -2;

  aseGetInfo(f, _model);
  aseAllocate(_model);
  aseGetData(f, _model);
  aseLoadTexture(_model);
#ifdef DEBUG
  aseDumpInfo(_model);
#endif

  fclose(f);

  return 0;
}


int Ase::Save(char *filename)
{
  FILE *f;
  int i;
  
	
  f = fopen(filename, "w");

  if (!f)
  {
    printf("Ase::Save> ERROR Couldn't open file '%s' for writing\n", filename);
    return -1;
  }

  if (!_model)
  {
    printf("Ase::Save> ERROR No data to save\n");
    return -2;
  }

#ifdef DEBUG
  aseDumpInfo(_model);
#endif

  // Header
  fprintf(f, "*3DSMAX_ASCIIEXPORT	200\n");
  fprintf(f, "*COMMENT \"AsciiExport Version  2.00 - GooseEgg\"\n");
  
  // Basic? info needed to make geo mesh
  fprintf(f, "*GEOMOBJECT {\n");
  fprintf(f, "	*NODE_NAME \"GooseEgg\"\n");
  fprintf(f, "	*NODE_TM {\n");
  fprintf(f, "		*NODE_NAME \"GooseEgg\"\n");
  fprintf(f, "		*INHERIT_POS 0 0 0\n");
  fprintf(f, "		*INHERIT_ROT 0 0 0\n");
  fprintf(f, "		*INHERIT_SCL 0 0 0\n");
  fprintf(f, "		*TM_ROW0  -0.0000	-1.0000	-0.0000\n");
  fprintf(f, "		*TM_ROW1  0.9936	-0.0000	0.1132\n");
  fprintf(f, "		*TM_ROW2  -0.1132	0.0000	0.9936\n");
  fprintf(f, "		*TM_ROW3  131.2377	-51.4771	4.7711\n");
  fprintf(f, "		*TM_POS   131.2377	-51.4771	4.7711\n");
  fprintf(f, "		*TM_ROTAXIS -0.0566	0.0566	0.9968\n");
  fprintf(f, "		*TM_ROTANGLE 1.5740\n");
  fprintf(f, "		*TM_SCALE 1.0000	1.0000	1.0000\n");
  fprintf(f, "		*TM_SCALEAXIS 0.0000	0.0000	0.0000\n");
  fprintf(f, "		*TM_SCALEAXISANG 0.0000\n");
  fprintf(f, "	}\n");
  fprintf(f, "	*MESH {\n");
  fprintf(f, "		*TIMEVALUE 0\n");

  //Start filling in mesh
  fprintf(f, "	  *MESH_NUMVERTEX %i\n", _model->numVertex);
  fprintf(f, "    *MESH_NUMFACES  %i\n", _model->numFaces);

  fprintf(f, "     *MESH_VERTEX_LIST {\n");

  for (i = 0; i < _model->numVertex; i++)
  {
    fprintf(f, "  *MESH_VERTEX    %i  %f %f %f\n", i,	
	    _model->verts[i][0], 
	    _model->verts[i][1],
	    _model->verts[i][2]);
  }

  fprintf(f, "     }\n");

  fprintf(f, "     *MESH_FACE_LIST {\n");

  for (i = 0; i < _model->numFaces; i++)
  {
    fprintf(f, "   *MESH_FACE  %i:\tA:\t%i B:\t%i C:\t%i\n", i,
	    _model->faces[i].vertIndex[0], 
	    _model->faces[i].vertIndex[1], 
	    _model->faces[i].vertIndex[2]);     
  } 

  fprintf(f, "     }\n");

  return 0;
}


////////////////////////////////////////////////////////////
// Private methods
////////////////////////////////////////////////////////////


ase_model_t *Ase::NewModel()
{
  ase_model_t *model;


  model = new ase_model_t;

  if (!model)
    return NULL;

  model->numVertex = 0;
  model->numFaces = 0;
  model->numTexFaces = 0;
  model->normals = 0;
  model->verts = NULL;
  model->vertNorms = NULL;
  model->faces = NULL;
  model->texVerts = NULL;
  model->texture.uTile = 0.0;
  model->texture.vTile = 0.0;
  model->texture.uOffset = 0.0;
  model->texture.uOffset = 0.0;
  model->texture.texId = 0;
  memset(model->texture.texName, '\0', sizeof (model->texture.texName));

  return model;
}


////////////////////////////////////////////////////////////
// TEST CODE
////////////////////////////////////////////////////////////

#ifdef TEST_ASE
int main(int argc, char *argv[])
{
  Ase ase;


  printf("[ASE class test]\n");

  if (argc > 2)
  {
    if (strcmp(argv[1], "load") == 0)
    {
      if (!ase.Load(argv[2]))
	printf("main: Load reports success.\n");
    }
    else if (strcmp(argv[1], "save") == 0)
    {
      // FIXME: Add code here to generate a small ase
      //
      //        Note I haven't added 'build your own' methods yet
      //        so I can't make the driver for it yet  =)

      if (!ase.Save(argv[2]))
	printf("main: Save reports success.\n");
    }
    else if (strcmp(argv[1], "test") == 0 && argc > 3)
    {
      if (!ase.Load(argv[2]))
	printf("main: Load reports success.\n");
      if (!ase.Save(argv[3]))
	printf("main: Save reports success.\n");
    }
    else
      printf("\n\n%s [save | load | test] filename.ase [testout.ase]\n", 
	     argv[0]);
  }
  else
  {
    printf("\n\n%s [save | load | test] filename.ase [testout.ase]\n", 
	   argv[0]);
  }
}
#endif
