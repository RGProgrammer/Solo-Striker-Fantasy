#include "Actor.h"

Actor::Actor(): m_ID(UNKNOWN),m_Pos({0.0f,0.0f,0.0f}),
                m_Dir({0.0f,0.0f,1.0f}),m_Up({0.0f,1.0f,0.0f}),
                m_TransMtx(NULL){
    m_TransMtx=(float*)malloc(16*sizeof(float));
    this->UpdateMtx();
};
Actor::Actor(Vertex3d Pos):Actor(){
    this->m_Pos=Pos ;
    this->UpdateMtx();
};
Actor::Actor(Vertex3d Pos,Vertex3d Dir,Vertex3d Up):Actor(Pos){
    if(DotProduct3d(Dir,Up)==0){
        m_Dir=Dir;
        m_Up=Up;
    }
};
Actor::~Actor(){
    this->Destroy();
} ;
void Actor::Destroy(){
   if(m_TransMtx!=NULL){
        free(m_TransMtx);
        m_TransMtx=NULL ;
    }
} ;
int Actor::getID(){
    return m_ID ;
};
float* Actor::getTransMtx(){
    this->UpdateMtx();
    return m_TransMtx;
};
int Actor::setOrientation(Vertex3d Dir,Vertex3d Up){
    if(DotProduct3d(Dir,Up)!=0.0f)//not perpendicular
        return 0 ;
    //else if Perpendicular
        m_Dir=Normalize3d(Dir) ;
        m_Up=Normalize3d(Up) ;
    return 1 ;
};
void Actor::setPosition(Vertex3d Pos){
    this->m_Pos=Pos;
};
Vertex3d Actor::getRight(){
    Vertex3d Right=CrossProduct3d(m_Dir,m_Up);
    return Right;
};
Vertex3d Actor::getDirection(){ return m_Dir;};
Vertex3d Actor::getPosition(){ return m_Pos;};
Vertex3d Actor::getUp(){return m_Up ;};
void Actor::Translate(Vertex3d Ver){
    m_Pos.x+=Ver.x;
    m_Pos.y+=Ver.y;
    m_Pos.z+=Ver.z;
};

void Actor::RotateViaUp(float ang){
    m_Dir=Rotate3d(m_Dir,m_Up,ang);
    Vertex3d Right=CrossProduct3d(m_Dir,m_Up);
    //Correction
    m_Up=CrossProduct3d(Right,m_Dir);
    m_Dir=Normalize3d(m_Dir);
    m_Up=Normalize3d(m_Up);
};
void Actor::RotateViaDirection(float ang){
    m_Up=Rotate3d(m_Up,m_Dir,ang);
    Vertex3d Right=CrossProduct3d(m_Dir,m_Up);
    //Correction
    m_Dir=CrossProduct3d(m_Up,Right);
    m_Dir=Normalize3d(m_Dir);
    m_Up=Normalize3d(m_Up);
};
void Actor::RotateViaRight(float ang){
    Vertex3d Right=CrossProduct3d(m_Dir,m_Up);
    m_Dir=Rotate3d(m_Dir,Right,ang);
    m_Up=CrossProduct3d(Right,m_Dir);
    m_Dir=Normalize3d(m_Dir);
    m_Up=Normalize3d(m_Up);
};
void Actor::UpdateMtx(){
        Vertex3d Right=Normalize3d(CrossProduct3d(m_Dir,m_Up));
        m_TransMtx[0]=Right.x; m_TransMtx[4]=m_Up.x; m_TransMtx[8]=m_Dir.x ; m_TransMtx[12]=m_Pos.x ;
        m_TransMtx[1]=Right.y; m_TransMtx[5]=m_Up.y; m_TransMtx[9]=m_Dir.y ; m_TransMtx[13]=m_Pos.y ;
        m_TransMtx[2]=Right.z; m_TransMtx[6]=m_Up.z; m_TransMtx[10]=m_Dir.z; m_TransMtx[14]=m_Pos.z;
        m_TransMtx[3]=0.0f    ; m_TransMtx[7]=0.0f ; m_TransMtx[11]=0.0f   ; m_TransMtx[15]=1.0f   ;
};
