#include "Math.h"
float Magnitude3d(Vertex3d Ver){
    return (float)sqrt(Ver.x*Ver.x+Ver.y*Ver.y+Ver.z*Ver.z);
};
Vertex3d Normalize3d(Vertex3d Ver){
    float d=Magnitude3d(Ver);
    return ScaleVertex3d(Ver,1.f/d);
};
Vertex3d AddVertex3d(Vertex3d Ver1 ,Vertex3d Ver2){
    return {Ver1.x+Ver2.x,Ver1.y+Ver2.y,Ver1.z+Ver2.z};
};
Vertex3d SubsVertex3d(Vertex3d Ver1,Vertex3d Ver2){
    return {Ver1.x+Ver2.x,Ver1.y+Ver2.y,Ver1.z+Ver2.z};
};
Vertex3d ScaleVertex3d(Vertex3d Ver,float s){
    return {Ver.x*s,Ver.y*s,Ver.z*s};
};
float DotProduct3d(Vertex3d Ver1 ,Vertex3d Ver2){
    return Ver1.x*Ver2.x+Ver1.y*Ver2.y+Ver1.z*Ver2.z;
};
Vertex3d CrossProduct3d(Vertex3d Ver1,Vertex3d Ver2){
    return {Ver1.y*Ver2.z-Ver1.z*Ver2.y,
            Ver1.z*Ver2.x-Ver1.x*Ver2.z,
            Ver1.x*Ver2.y-Ver1.y*Ver2.x};
};
Vertex3d Rotate3d(Vertex3d Ver,Vertex3d Pers,double ang ){
    Pers=Normalize3d(Pers);
    Vertex3d tmp ;
    tmp.x=Ver.x*(cos(ang)+Pers.x*Pers.x*(1-cos(ang)))+
          Ver.y*(Pers.x*Pers.y*(1-cos(ang))-Pers.z*sin(ang))+
          Ver.z*(Pers.x*Pers.z*(1-cos(ang))+Pers.z*sin(ang));
    tmp.y=Ver.x*(Pers.x*Pers.y*(1-cos(ang))+Pers.z*sin(ang))+
          Ver.y*(cos(ang)+Pers.y*Pers.y*(1-cos(ang)))+
          Ver.z*(Pers.y*Pers.z*(1-cos(ang))-Pers.x*sin(ang));
    tmp.z=Ver.x*(Pers.x*Pers.z*(1-cos(ang))-Pers.y*sin(ang))+
          Ver.y*(Pers.y*Pers.z*(1-cos(ang))+Pers.x*sin(ang))+
          Ver.z*(cos(ang)+Pers.z*Pers.z*(1-cos(ang)));
    return tmp;

};
void Multi4x4Mtx(float* leftMtx, float* rightMtx,float* resultMtx){
        resultMtx[0] =leftMtx[0]*rightMtx[0]+leftMtx[4]*rightMtx[1]+leftMtx[8]*rightMtx[2] +leftMtx[12]*rightMtx[3];
        resultMtx[1] =leftMtx[1]*rightMtx[0]+ leftMtx[5]*rightMtx[1]+leftMtx[9]*rightMtx[2] +leftMtx[13]*rightMtx[3];
        resultMtx[2] =leftMtx[2]*rightMtx[0]+ leftMtx[6]*rightMtx[1]+leftMtx[10]*rightMtx[2]+leftMtx[14]*rightMtx[3];
        resultMtx[3] =leftMtx[3]*rightMtx[0]+ leftMtx[7]*rightMtx[1]+leftMtx[11]*rightMtx[2]+leftMtx[15]*rightMtx[3];
        resultMtx[4] =leftMtx[0]*rightMtx[4]+ leftMtx[4]*rightMtx[5]+leftMtx[8]*rightMtx[6] +leftMtx[12]*rightMtx[7];
        resultMtx[5] =leftMtx[1]*rightMtx[4]+ leftMtx[5]*rightMtx[5]+leftMtx[9]*rightMtx[6] +leftMtx[13]*rightMtx[7];
        resultMtx[6] =leftMtx[2]*rightMtx[4]+ leftMtx[6]*rightMtx[5]+leftMtx[10]*rightMtx[6]+leftMtx[14]*rightMtx[7];
        resultMtx[7] =leftMtx[3]*rightMtx[4]+ leftMtx[7]*rightMtx[5]+leftMtx[11]*rightMtx[6]+leftMtx[15]*rightMtx[7];
        resultMtx[8] =leftMtx[0]*rightMtx[8]+ leftMtx[4]*rightMtx[9]+leftMtx[8]*rightMtx[10]+leftMtx[12]*rightMtx[11];
        resultMtx[9] =leftMtx[1]*rightMtx[8]+ leftMtx[5]*rightMtx[9]+leftMtx[9]*rightMtx[10]+leftMtx[13]*rightMtx[11];
        resultMtx[10]=leftMtx[2]*rightMtx[8]+ leftMtx[6]*rightMtx[9]+leftMtx[10]*rightMtx[10]+leftMtx[14]*rightMtx[11];
        resultMtx[11]=leftMtx[3]*rightMtx[8]+ leftMtx[7]*rightMtx[9]+leftMtx[11]*rightMtx[10]+leftMtx[15]*rightMtx[11];
        resultMtx[12]=leftMtx[0]*rightMtx[12]+leftMtx[4]*rightMtx[13]+leftMtx[8]*rightMtx[14]+leftMtx[12]*rightMtx[15];
        resultMtx[13]=leftMtx[1]*rightMtx[12]+leftMtx[5]*rightMtx[13]+leftMtx[9]*rightMtx[14]+leftMtx[13]*rightMtx[15];
        resultMtx[14]=leftMtx[2]*rightMtx[12]+leftMtx[6]*rightMtx[13]+leftMtx[10]*rightMtx[14]+leftMtx[14]*rightMtx[15];
        resultMtx[15]=leftMtx[3]*rightMtx[12]+leftMtx[7]*rightMtx[13]+leftMtx[11]*rightMtx[14]+leftMtx[15]*rightMtx[15];
};
//void Multi4x4Mtx(float* leftMtx, float* rightMtx,float* resultMtx){
//}
