////////////////////////////////////////////////////////////////
//                      StaticModel                          //
//              StaticModel is a Static 3d Model             //
//                                                            //
////////////////////////////////////////////////////////////////
#ifndef PFE_StaticModel_H_
#define PFE_StaticModel_H_
#include "Abstract.h"
#include "Types.h"
#include <stdio.h>
#include <GL//gl.h>
class StaticModel : public Drawable {
public:
    //Constructor
    StaticModel();
    StaticModel(Vertex3d Pos);
    StaticModel(Vertex3d Pos,Vertex3d Dir,Vertex3d Up);
    //Deconstructor
    virtual ~StaticModel();
    //load the 3d model from a file: 1=Success ,0=Failed
    virtual int LoadFromFile(char* filename);
    //this method define how the 3d moidel is drawn
    void Draw(float * ViewMtx);
    //Scale the 3d model
    void Scale(float );
    //free Resources
    virtual void Destroy();
    //setters and getters
    void setColor(ColorRGB Color);
    ColorRGB getColor();
    //helps create a 3d cube
    static StaticModel* CreateCube();
    //loads a 3d model and return its reference
    static StaticModel* LoadFile(char* filename);
    //clone Meshes from another mocel
    virtual int Clone (StaticModel* Model);

protected :
    int AddMesh(char*);//add a mesh refernece to vector
    int addVertex(Vertex3d);//add a vertex to Vertxtexbuffer of the selected mesh(used by loadfromfile method)
    int addNormal(Vertex3d);//add a vertex to Normalbuffer of the selected mesh(used by loadfromfile method)
    int addIndices(unsigned int id1,unsigned int id2,unsigned int id3);// add Face to indicesbuffer
    int addTexCoord(Vertex2d);//add to texture coordinate to texture coordinates buffer
    void extractFace(char* line,unsigned int *,unsigned int *,unsigned int *);
    static void ReadLine(FILE* file ,char* buffer);
    void UpdateMtx();
    ColorRGB                m_Color ;//Color used if the meshes has no material
    float                   m_Scale ;//Scale of the 3d model(>0);
    unsigned int            m_nbMeshes;//number of meshes construcring this model
    Mesh*                   v_Meshes ;// vector of meshes
};
#endif // PFE_StaticModel_H_
