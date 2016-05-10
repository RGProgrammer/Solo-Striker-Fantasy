#include "Blades.h"

Blades::Blades():Enemy(){
};
Blades::Blades(Vertex3d Pos):Enemy(Pos){
};
Blades::Blades(Vertex3d Pos ,Vertex3d Dir,Vertex3d Up ):Enemy(Pos,Dir,Up){
};
Blades::~Blades(){
    this->Destroy();
}
int Blades::LoadFromFile(){
    m_Health=20.0f;
    m_Explosion=new Explosion(this);
    m_Explosion->LoadFromFile();
    return StaticModel::LoadFromFile("Data//blades.obj");
};
void Blades::Update(float dt){
    Enemy::Update(dt);
};
int Blades::Clone(Blades* Clone){
    return StaticModel::Clone(Clone);
};
int Blades::Fire(Vertex3d Direction ){

};
