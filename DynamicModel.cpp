#include "DynamicModel.h"

DynamicModel::DynamicModel():StaticModel(),Updatable(),m_Velocity({0.0f,0.0f,0.0f}),m_Dt(0.0f){
    m_ID=DRAWABLE|UPDATABLE;
};
DynamicModel::DynamicModel(Vertex3d Pos):StaticModel(Pos),Updatable(),m_Velocity({0.0f,0.0f,0.0f}),m_Dt(0.0f){
    m_ID=DRAWABLE|UPDATABLE;
};
DynamicModel::DynamicModel(Vertex3d Pos,Vertex3d Dir,Vertex3d Up):StaticModel(Pos,Dir,Up),Updatable(),
                                                                    m_Velocity({0.0f,0.0f,0.0f}),
                                                                    m_Dt(0.0f){
    m_ID=DRAWABLE|UPDATABLE;
};
DynamicModel::~DynamicModel(){
    this->Destroy();
};
int DynamicModel::Clone(DynamicModel * Model){
    m_Velocity=Model->m_Velocity;
    return Clone(Model);
};
void DynamicModel::Destroy(){
    StaticModel::Destroy();
};
