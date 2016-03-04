#include "ShotTypes.h"

EnergyBullet::EnergyBullet():Shot(){
    m_Damage=5 ;
    m_Source=NULL;
    m_Speed=2.0f;
    m_LifeTime=2.0f;
    m_Velocity=ScaleVertex3d(Normalize3d(StaticModel::m_Dir),m_Speed);
};
EnergyBullet::EnergyBullet(Vertex3d Pos,Vertex3d Dir,Vertex3d Up):Shot(Pos,Dir,Up){
    m_Damage=5 ;
    m_Source=NULL;
    m_Speed=2.0f;
    m_Velocity=ScaleVertex3d(Normalize3d(m_Dir),m_Speed);
    m_LifeTime=2.0f;
};
EnergyBullet::EnergyBullet(Actor* Source):Shot(){
    m_Damage=5 ;
    m_Source=NULL;
    m_Speed=2.0f;
    m_Velocity=ScaleVertex3d(Normalize3d(m_Dir),m_Speed);
    m_LifeTime=2.0f;
};
EnergyBullet::~EnergyBullet(){

};
void EnergyBullet::Update(float dt){
    if(dt==0)
        dt=0.1f;
    m_Dt=+dt;
    if(m_Dt>=m_LifeTime)
        m_ID=0x0000 ;
  m_Pos=AddVertex3d(m_Pos,ScaleVertex3d(m_Velocity,dt));
};
int EnergyBullet::LoadFromFile(){
    return StaticModel::LoadFromFile("Data//shot.obj");
};


Chaser::Chaser(){

};
Chaser::~Chaser(){

};


SmallShot::SmallShot():Shot(){
    m_Source=NULL;
    m_Speed=2.0f;
    m_LifeTime=2.0f;
    m_Velocity=ScaleVertex3d(Normalize3d(StaticModel::m_Dir),m_Speed);
};
SmallShot::SmallShot(Vertex3d Pos,Vertex3d Dir,Vertex3d Up):Shot(Pos,Dir,Up){
     m_Source=NULL;
    m_Speed=2.0f;
    m_LifeTime=2.0f;
    m_Velocity=ScaleVertex3d(Normalize3d(StaticModel::m_Dir),m_Speed);
};
SmallShot::SmallShot(Actor* Source):Shot(){
     m_Source=Source;
    m_Speed=2.0f;
    m_LifeTime=2.0f;
    m_Velocity=ScaleVertex3d(Normalize3d(StaticModel::m_Dir),m_Speed);
};
SmallShot::~SmallShot(){

};
void SmallShot::Update(float dt){
    if(dt==0)
        dt=0.1f;
    m_Dt=+dt;
    if(m_Dt>=m_LifeTime)
        m_ID=0x0000 ;
  m_Pos=AddVertex3d(m_Pos,ScaleVertex3d(m_Velocity,dt));
};
int SmallShot::LoadFromFile(){
    return StaticModel::LoadFromFile("Data//shot.obj");
};


LongShot::LongShot(){
};
LongShot::~LongShot(){
};
