#include "DynamicModel.h"

DynamicModel::DynamicModel():Updatable(),StaticModel(),m_Velocity({0.0f,0.0f,0.0f}){
    StaticModel::m_ID=DRAWABLE|UPDATABLE;
};
DynamicModel::DynamicModel(Vertex3d Pos):StaticModel(Pos),m_Velocity({0.0f,0.0f,0.0f}){
    StaticModel::m_ID=DRAWABLE|UPDATABLE;
};
DynamicModel::DynamicModel(Vertex3d Pos,Vertex3d Dir,Vertex3d Up):StaticModel(Pos,Dir,Up),m_Velocity({0.0f,0.0f,0.0f}){
    StaticModel::m_ID=DRAWABLE|UPDATABLE;
};
DynamicModel::~DynamicModel(){
    this->Destroy();
};
void DynamicModel::Destroy(){
    StaticModel::Destroy();
};
