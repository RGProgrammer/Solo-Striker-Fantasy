#include "Camera.h"
#include <stdio.h>
Camera::Camera():Actor(),m_ViewType(FREE){
    this->UpdateMtx();
};
Camera::~Camera(){ Destroy();};
int Camera::getViewType(){
    return m_ViewType ;
};
void Camera::setViewType(int Type){
    if(Type==UP){
        m_ViewType=UP ;
        this->setOrientation({0.0f,-1.0f,0.0f},{0.0f,0.0f,-1.0f});
        this->setPosition({0.0f,150.0f,0.0f});
    }
    if(Type==SIDE){
        m_ViewType=SIDE;
        setOrientation({-1.0f,0.0f,0.0f},{0.0f,-1.0f,0.0f});
        setPosition({150.0f,0.0f,0.0f});
    }
    if(Type==FREE)
        m_ViewType=FREE ;
};

void Camera::printInfo(){
    if(m_ViewType==UP)
        printf("Camera Up view: \n");
    else
        printf("Camera Side view: \n");
    printf("Pos: %f %f %f\n",m_Pos.x,m_Pos.y,m_Pos.z);
    printf("Dir : %f   %f   %f\n",m_Dir.x,m_Dir.y,m_Dir.z);
    printf("Up : %f   %f   %f\n",m_Up.x,m_Up.y,m_Up.z);
};
void Camera::UpdateMtx(){
    Vertex3d Forward =Normalize3d(SubsVertex3d(m_Pos,m_Dir));
    Vertex3d Side=Normalize3d(CrossProduct3d(m_Up,Forward));
    Vertex3d Up=CrossProduct3d(Forward,Side);
        m_TransMtx[0]=Side.x; m_TransMtx[4]=Up.x; m_TransMtx[8]=(-m_Dir.x) ; m_TransMtx[12]=-DotProduct3d(Side,m_Pos);
        m_TransMtx[1]=Side.y; m_TransMtx[5]=Up.y; m_TransMtx[9]=(-m_Dir.y) ; m_TransMtx[13]=-DotProduct3d(Up,m_Pos) ;
        m_TransMtx[2]=Side.z; m_TransMtx[6]=Up.z; m_TransMtx[10]=(-m_Dir.z); m_TransMtx[14]=-DotProduct3d(Forward,m_Pos);
        m_TransMtx[3]=0.0f    ; m_TransMtx[7]=0.0f  ; m_TransMtx[11]=0.0f   ; m_TransMtx[15]=1.0f   ;
};
