#ifndef PFE_NUMBERGENERATOR_H_
#define PFE_NUMBERGENERATOR_H_
#include "Abstract.h"
#include "Math.h"
#include "Types.h"
#include ".//tools//sdl2//include//SDL_opengl.h"
#include ".//tools//lodepng//lodepng.h"
#include <stdio.h>
//the current version only transform an integer into StaticMoodel
class GNumber: public Drawable {
public:
    GNumber();
    ~GNumber();
    void Destroy();
    void AddValue(unsigned int  Value);
    void setNBDigits(unsigned int Nb);
    void setValue(unsigned int  Value);
    void setScale(float value);
    unsigned int getValue();
    //void setPosition(Vertex2d Pos);
    //int setOrientation(Vertex2d Dir);
    void Draw(float* ViewMtx);
private:
    //generate Meshes
    int GenerateMesh();
    // reloacate each texcoord in to the correspendant nomber in the texture
    int  RegenTextureCoord();
    void UpdateMtx();
    unsigned int            m_Value;
    unsigned int            m_nbDigit;
    Vertex3d*               v_VertexBuffer ;   //points coordinates buffer that construct the Mesh
    unsigned int            m_nbVertices ;   //number of point of the mesh
    Index*                  v_IndexBuffer ; //buffer contains indicies of points(used to link mesh points to construct surfaces)
    unsigned int            m_Faces ;      //number of surface used on this mesh(each surface cosntructed by 3 points)
    Vertex3d*               v_NormalsBuffer ; //buffer for Normmals
    unsigned int            m_nbNormals;   //number of normals
    Vertex2d*               v_TexCoords;      //buffer of texture coords
    unsigned int            m_nbTexCoords ;//number of texture coordinates
    Material*               m_Material ;
    float                   m_Scale;

};
#endif // PFE_TEXTGENERATOR_H_
