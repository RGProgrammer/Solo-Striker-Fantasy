#include "FIRST.h"

FIRST::FIRST():Boss(){
};
FIRST::FIRST(Vertex3d Pos):Boss(Pos){
};
FIRST::FIRST(Vertex3d Pos,Vertex3d Dir, Vertex3d Up):Boss(Pos,Dir,Up){
};
FIRST::~FIRST(){
    this->Destroy();
};
int FIRST::LoadFromFile(){
    m_Explosion=new Explosion(this);
    m_Explosion->LoadFromFile();
    m_Health=3000;
    return StaticModel::LoadFromFile("Data//FIRST.obj");
};
void FIRST::Destroy(){
    Boss::Destroy();
};
