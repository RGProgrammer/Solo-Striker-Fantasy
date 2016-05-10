#include "UFO.h"

UFO::UFO():Enemy(){
};
UFO::UFO(Vertex3d Pos):Enemy(Pos){
};
UFO::UFO(Vertex3d Pos, Vertex3d Dir, Vertex3d Up):Enemy(Pos,Dir,Up){
};
int UFO::LoadFromFile(){
    StaticModel::LoadFromFile("Data//UFO.obj");
    m_Explosion=new Explosion(this);
    m_Explosion->LoadFromFile();
    this->setColor({5.0f,0.0f,0.5f});
    m_Health=1 ;
    m_Dt=0.0f;
};
int UFO::Fire(Vertex3d Direction){

};
