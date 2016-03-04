#ifndef PFE_OBJLOADER_H_
#define PFE_OBJLOADER_H_
#include "StaticModel.h"
#include <stdio.h>
#include <stdlib.h>
class StaticModel;
class ObjLoader {
public :
    ObjLoader();
    ~ObjLoader();
     void Release();
     int loadObjfile(char* objfilename);
    int CopyBuffer(StaticModel* Dest);
    int loadMaterial(char* mtlfilename);
    static int LoadFile(StaticModel* dest,char* filename);
private:
    int CalculNormals();
    void extractFace(char* line,unsigned int *,unsigned int *,unsigned int *);
    int AddMesh(char*);
    int addVertex(Vertex3d);
    int addNormal(Vertex3d);
    int addIndices(unsigned int id1,unsigned int id2,unsigned int id3);
    static void ReadLine(FILE* file ,char* buffer);
    void InitMinMaxVertices ();
    ColorRGB                m_Color ;//Color used if the meshes has no material
    float                   m_Scale ;//Scale of the 3d model(>0);
    unsigned int            m_nbMeshes;//number of meshes construcring this model
    Mesh*                   v_Meshes ;
};
#endif // PFE_OBJLOADER_H_
