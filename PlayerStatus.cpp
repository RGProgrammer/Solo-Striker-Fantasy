#include "PlayerStatus.h"

PlayerStatus::PlayerStatus():m_Shield(0),m_Icon(NULL),m_ShIconSample(NULL){
};
PlayerStatus::~PlayerStatus(){
    this->Destroy();
};
void PlayerStatus::Destroy(){
    StaticModel::Destroy();
    m_Icon=NULL ;
};
int PlayerStatus::LoadFromFile(){
    m_Shield=3 ;
    this->setPosition({-3.01f,-3.55f,-10.f});
    m_ShIconSample=new StaticModel();
    m_ShIconSample->LoadFromFile("Data//ShLevelIcon.obj");
    m_ShIconSample->setPosition({-2.3f,-3.85f,-10.0f});
    m_ShIconSample->setColor({0.0f,1.0f,0.0f});
    return StaticModel::LoadFromFile("Data//Player_Status.obj");
};
void PlayerStatus::Draw(float * Matrix){
    float tab[16];
    StaticModel::Draw(NULL);
    if(m_Icon){
        m_Icon->Draw(NULL);
    }
    if(m_ShIconSample){
        Vertex3d original=m_ShIconSample->getPosition();
        for(int i=0 ;i<m_Shield;i++){
            m_ShIconSample->setPosition(AddVertex3d(original,{i*0.5f,0.0f,0.0f}));
            m_ShIconSample->Draw(NULL);
        }
        m_ShIconSample->setPosition(original);
    }
};
void PlayerStatus::setIcon(StaticModel* Icon){
    m_Icon=Icon ;
    if(m_Icon){
        m_Icon->setPosition({-2.0f,-3.25f,-9.9f});
    }
};
int PlayerStatus::getShieldValue(){
    return m_Shield ;
};
void PlayerStatus::setShieldValue(int Value){
    m_Shield=Value;
};
