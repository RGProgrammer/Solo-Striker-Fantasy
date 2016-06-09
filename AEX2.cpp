#include "AEX2.h"

AEX2::AEX2():Enemy(){
};
AEX2::AEX2(Vertex3d Pos):Enemy(Pos){
};
AEX2::AEX2(Vertex3d Pos, Vertex3d Dir,Vertex3d Up):Enemy(Pos,Dir,Up){
};
AEX2::~AEX2(){
    this->Destroy();
};
int AEX2::LoadFromFile(){
    m_Health=20.0f;
    m_Explosion=new Explosion(this);
    m_Explosion->LoadFromFile();
    return StaticModel::LoadFromFile("Data//AeX2.obj");
};
void AEX2::Update(float dt){
    Enemy::Update(dt);
};
int AEX2::Clone(AEX2* Clone){
    return StaticModel::Clone(Clone);
};

