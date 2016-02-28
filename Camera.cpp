#include "Camera.h"

Camera::Camera():Actor(){};
Camera::~Camera(){ Destroy();};
/*void Camera::printInfo(){
    printf("Camera:\n");
    printf("Dir : %f   %f   %f\n",m_Dir.x,m_Dir.y,m_Dir.z);
    printf("Up : %f   %f   %f\n",m_Up.x,m_Up.y,m_Up.z);
    printf("Left : %f   %f   %f\n",m_Right.x,m_Right.y,m_Right.z);
    printf("Dir Dot UP  %f\n",DotProduct3d(m_Dir,m_Up));
    printf("Dir Dot left  %f\n",DotProduct3d(m_Dir,m_Right));
    printf("left Dot UP  %f\n",DotProduct3d(m_Right,m_Up));
};*/
void Camera::UpdateMtx(){
    m_Right=Normalize3d(m_Right);m_Up=Normalize3d(m_Up);m_Dir=Normalize3d(m_Dir);
        m_TransMtx[0]=m_Right.x; m_TransMtx[4]=m_Up.x; m_TransMtx[8]=m_Dir.x ; m_TransMtx[12]=m_Pos.x*m_Right.x+m_Up.x*m_Pos.y+m_Dir.x*m_Pos.z ;
        m_TransMtx[1]=m_Right.y; m_TransMtx[5]=m_Up.y; m_TransMtx[9]=m_Dir.y ; m_TransMtx[13]=m_Pos.x*m_Right.y+m_Up.y*m_Pos.y+m_Dir.y*m_Pos.z ;
        m_TransMtx[2]=m_Right.z; m_TransMtx[6]=m_Up.z; m_TransMtx[10]=m_Dir.z; m_TransMtx[14]=m_Pos.x*m_Right.z+m_Up.z*m_Pos.y+m_Dir.z*m_Pos.z;
        m_TransMtx[3]=0.0f    ; m_TransMtx[7]=0.0f  ; m_TransMtx[11]=0.0f   ; m_TransMtx[15]=1.0f   ;
};
