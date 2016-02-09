#include "Abstract.h"
Drawable::Drawable():Actor(){
    m_ID|= DRAWABLE ;
};
Drawable::Drawable(Vertex3d Pos):Drawable(){
    m_Pos=Pos ;
};
Drawable::Drawable(Vertex3d Pos,Vertex3d Dir,Vertex3d Up):Drawable(Pos){
    if(DotProduct3d(Dir,Up)==0.0f){
        m_Dir=Dir ;
        m_Up=Up ;
    }
};
Drawable::~Drawable(){};

Updatable::Updatable():Actor(){
    m_ID|= UPDATABLE ;
};
Updatable::Updatable(Vertex3d Pos):Updatable(){
     m_Pos=Pos ;
};
Updatable::Updatable(Vertex3d Pos,Vertex3d Dir,Vertex3d Up):Updatable(Pos){
     if(DotProduct3d(Dir,Up)==0.0f){
        m_Dir=Dir ;
        m_Up=Up ;
    }
};
Updatable::~Updatable(){};

DnU::DnU():Drawable(),Updatable(){
    Drawable::m_ID=DRAWABLE|UPDATABLE ;
};
DnU::DnU(Vertex3d Pos):DnU(){
     Drawable::m_Pos=Pos ;
};
DnU::DnU(Vertex3d Pos,Vertex3d Dir,Vertex3d Up):DnU(Pos){
     if(DotProduct3d(Dir,Up)==0.0f){
        Drawable::m_Dir=Dir ;
        Drawable::m_Up=Up ;
    }
};
    //Deconstructor
DnU::~DnU(){};
