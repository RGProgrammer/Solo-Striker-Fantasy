#ifndef PFE_OBJLOADER_H_
#define PFE_OBJLOADER_H_
#include "Types.h"
#include "StaticModel.h"
#include <stdio.h>
#include <string.h>


void ReadLine(FILE* file,char* buffer);
bool contains(char* str1,char* str2);

class StaticModel ;
class ObjLoader {
public:
    static int LoadModel(char* filename,StaticModel *Dest);
private :
    ObjLoader();
    ~ObjLoader();
    void Release();
    int LoadObjFile(char* filename);
    int LoadMtlFile(char* filename);
    int CopyBuffer(StaticModel* Dest);
    int AddMesh(char*);//add a mesh refernece to vector
    int addVertex(Vertex3d);//add a vertex to Vertxtexbuffer of the selected mesh(used by loadfromfile method)
    int addNormal(Vertex3d);//add a vertex to Normalbuffer of the selected mesh(used by loadfromfile method)
    int addIndices(Index id1,Index id2,Index id3);// add Face to indicesbuffer
    int addTexCoord(Vertex2d);//add to texture coordinate to texture coordinates buffer
    void InitMinMaxVertices ();
    pMesh               v_Meshes ;
    unsigned int        m_nbMeshes;
    Material*           v_Materials ;
    int                 m_nbMaterial ;



};
#endif // PFE_OBJLOADER_H_
