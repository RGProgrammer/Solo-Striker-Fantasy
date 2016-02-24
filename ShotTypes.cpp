#include "ShotTypes.h"

EnergyBullet::EnergyBullet():Shot(){
    m_Source=NULL;
    m_Speed=2.0f;
    m_Velocity=ScaleVertex3d(Normalize3d(StaticModel::m_Dir),m_Speed);

};
EnergyBullet::EnergyBullet(Vertex3d Pos,Vertex3d Dir,Vertex3d Up):Shot(Pos,Dir,Up){
    m_Source=NULL;
    m_Speed=2.0f;
    m_Velocity=ScaleVertex3d(Normalize3d(StaticModel::m_Dir),m_Speed);
};
EnergyBullet::EnergyBullet(Actor* Source):Shot(){
    m_Source=NULL;
    m_Speed=2.0f;
    m_Velocity=ScaleVertex3d(Normalize3d(StaticModel::m_Dir),m_Speed);
};
EnergyBullet::~EnergyBullet(){

};
void EnergyBullet::Update(float dt){
    StaticModel::m_Pos=AddVertex3d(StaticModel::m_Pos,ScaleVertex3d(m_Velocity,dt));
};
int EnergyBullet::LoadFromFile(){
    return StaticModel::LoadFromFile("Data//shot.obj");
};


Chaser::Chaser(){

};
Chaser::~Chaser(){

};


SmallShot::SmallShot(){
};
SmallShot::~SmallShot(){
};


LongShot::LongShot(){
};
LongShot::~LongShot(){
};
