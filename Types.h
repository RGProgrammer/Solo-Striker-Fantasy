////////////////////////////////////////////////////////////////////
//                      Types                                     //
//this file contains definitions of all needed types/Structures   //
// for this project                                               //
//                                                                //
////////////////////////////////////////////////////////////////////
#ifndef PFE_TYPES_H_
#define PFE_TYPES_H_
#include "Math.h"
typedef struct {
    int Width;  //width of the image
    int Height; //height of the image
    char* Pixels; // Buffer of RGBA Values(R:red ,G:green,B:blue,A:alpha/transperancy)
} Image ;
typedef struct {
    char* mtlName;
    Image* TextureMap ;
    Image* BumpMap ;
    Image* ReflexionMap ;
    Image* MaterialMap ;
} Material ; // all needed types of images that can be applied on 3d model
typedef struct{
    float r,g,b;
} ColorRGB ;
typedef struct{
    float r,g,b,a;
} ColorRGBA ;
typedef struct {
    unsigned int VertexIndex;
    unsigned int NormalIndex;
    unsigned int TexIndex ;
    //a valid value of these attributs start from 1
} Index;
typedef struct {
    char* Name ;                //name of the mesh
    Vertex3d* VertexBuffer ;   //points coordinates buffer that construct the Mesh
    unsigned int nbVertices ;   //number of point of the mesh
    Index* IndexBuffer ; //buffer contains indicies of points(used to link mesh points to construct surfaces)
    unsigned int Faces ;      //number of surface used on this mesh(each surface cosntructed by 3 points)
    Vertex3d* NormalsBuffer ; //buffer for Normmals
    unsigned int nbNormals;   //number of normals
    Vertex2d* TexCoords;      //buffer of texture coords
    unsigned int nbTexCoords ;//number of texture coordinates
    Material* material ; //Material
    //these 2 attributes are used to construct AABB(a collision box/cube used by the Physics engine)
    Vertex3d MinVertex; //Min local space Coordinate
    Vertex3d MaxVertex; //Max local space Coordinate
} Mesh , *pMesh ; // a part of a 3d Model. a 3d model is constructed of 1 to many meshes

#endif // PFE_TYPES_H_
