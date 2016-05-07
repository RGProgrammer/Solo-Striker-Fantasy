#include "Canon.h"

Canon::Canon():Enemy(){
};
Canon::Canon(Vertex3d Pos):Enemy(Pos){
};
Canon::Canon(Vertex3d Pos ,Vertex3d Dir,Vertex3d Up):Enemy(Pos,Dir,Up){
};
Canon::~Canon(){
    this->Destroy() ;
};
int Canon::LoadFromFile() {
    m_Health=150.0f;
    m_Explosion=new Explosion(this);
    m_Explosion->LoadFromFile("Data//Explosion.obj");
    return StaticModel::LoadFromFile("Data//Canon.obj");
};
void Canon::Update(float dt){
    Enemy::Update(dt);
};
