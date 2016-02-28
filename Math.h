//////////////////////////////////////////////////////////////
//                      Math                                //
//this is Math library that contains nearly all operation   //
//applied on Vertices and Matrices                          //
//                                                          //
//////////////////////////////////////////////////////////////
#ifndef PFE_MATH_H_
#define PFE_MATH_H_
#include <math.h>
typedef struct {
    float x,y,z ;
} Vertex3d,Point3d,Normal3d ;
typedef struct {
    float u,v ;
} Vertex2d,Point2d,Normal2d ;
float Magnitude3d(Vertex3d);
Vertex3d Normalize3d(Vertex3d);
Vertex3d AddVertex3d(Vertex3d,Vertex3d);// sum of 2 vertices
Vertex3d SubsVertex3d(Vertex3d,Vertex3d);
Vertex3d ScaleVertex3d(Vertex3d,float);
float DotProduct3d(Vertex3d,Vertex3d);//
Vertex3d CrossProduct3d(Vertex3d,Vertex3d);
Vertex3d Rotate3d(Vertex3d,Vertex3d,double );
void Multi4x4Mtx(float* , float*,float*);
Vertex3d Mtx_x_Vertex(float* M4x4,Vertex3d ver);
#endif // PFE_MATH_H_

