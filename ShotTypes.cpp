#include "ShotTypes.h"

EnergyBullet::EnergyBullet():Shot(){
    m_Damage=5 ;
    m_Source=NULL;
    m_Speed=100.0f;
    m_LifeTime=10.0f;
    setColor({0.98f,0.73f,0.16f});
};
EnergyBullet::EnergyBullet(Vertex3d Pos,Vertex3d Dir,Vertex3d Up):Shot(Pos,Dir,Up){
    m_Damage=5 ;
    m_Source=NULL;
    m_Speed=100.0f;
    m_LifeTime=10.0f;
    setColor({0.98f,0.73f,0.16f});
};
EnergyBullet::EnergyBullet(Actor* Source):Shot(Source){
    m_Damage=5 ;
    m_Speed=100.0f;
    m_LifeTime=100.0f;
    setColor({0.98f,0.73f,0.16f});
};
EnergyBullet::~EnergyBullet(){
};
void EnergyBullet::Update(float dt){
    m_LifeTime-=dt;
    m_Velocity=ScaleVertex3d(m_Dir,m_Speed*dt);
    m_Pos=AddVertex3d(m_Pos,m_Velocity);
    if(Magnitude3d(SubsVertex3d({0.0f,0.0f,0.0f},m_Pos))>250.0f || m_LifeTime<=0)
        m_ID=UNKNOWN ;
};
int EnergyBullet::LoadFromFile(){
    return StaticModel::LoadFromFile("Data//EnergyBullet.obj");
};
Shot* EnergyBullet::Clone(){
    Shot* clone=new EnergyBullet();
    clone->DynamicModel::Clone(this);
    clone->setLifeTime(m_LifeTime) ;
    clone->setSource(m_Source);
    clone->setSpeed(m_Speed );
    clone->setDamage(m_Damage) ;
};
void EnergyBullet::Hit(){
    m_Speed=0.0f;
    m_Velocity={0.0f,0.0f,0.0f};
    m_ID=UNKNOWN;
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
    m_Dt+=dt;
    if(m_Dt>=m_LifeTime)
        m_ID=UNKNOWN ;
  m_Pos=AddVertex3d(m_Pos,ScaleVertex3d(m_Velocity,dt));
};
int SmallShot::LoadFromFile(){
    return StaticModel::LoadFromFile("Data//SmallShot.obj");
};
Shot* SmallShot::Clone(){
    Shot* clone=new SmallShot();
    clone->DynamicModel::Clone(this);
    clone->setLifeTime(m_LifeTime) ;
    clone->setSource(m_Source);
    clone->setSpeed(m_Speed );
    clone->setDamage(m_Damage) ;
};
void SmallShot::Hit(){
    m_Speed=0.0f;
    m_Velocity={0.0f,0.0f,0.0f};
    //m_ID=UNKNOWN;
};

LongShot::LongShot():Shot(){
    m_Damage=1 ;
    m_Source=NULL;
    m_Speed=50.0f;
    m_LifeTime=10.0f;
    setColor({0.0f,1.0f,0.0f});
};
LongShot::LongShot(Vertex3d Pos, Vertex3d Dir, Vertex3d Up):Shot(Pos,Dir,Up){
    m_Damage=1 ;
    m_Source=NULL;
    m_Speed=50.0f;
    m_LifeTime=10.0f;
    setColor({0.0f,1.0f,0.0f});

};
LongShot::LongShot(Actor* Source):Shot(Source){
    m_Damage=1 ;
    m_Speed=50.0f;
    m_LifeTime=10.0f;
    setColor({0.0f,1.0f,0.0f});

};
LongShot::~LongShot(){
    this->Destroy();
};
void LongShot::Update(float dt){
    m_LifeTime-=dt;
    if(m_LifeTime<=0.0f){
        m_ID=UNKNOWN ;
        return ;
    }
    m_Velocity=ScaleVertex3d(m_Dir,m_Speed*dt);
    m_Pos=AddVertex3d(m_Pos,m_Velocity);
};
int LongShot::LoadFromFile(){
    return StaticModel::LoadFromFile("Data//LongShot.obj");
};
Shot* LongShot::Clone(){
    Shot* clone=new LongShot();
    clone->DynamicModel::Clone(this);
    clone->setLifeTime(m_LifeTime) ;
    clone->setSource(m_Source);
    clone->setSpeed(m_Speed );
    clone->setDamage(m_Damage) ;
};
void LongShot::Hit(){
    m_ID=UNKNOWN ;
};

Laser::Laser():Shot(){
    m_Source=NULL;
    m_Speed=0.0f;
    m_LifeTime=2.5f;
    m_Velocity={0.0f,0.0f,0.0f};
};
Laser::Laser(Vertex3d Pos, Vertex3d Dir, Vertex3d Up):Shot(Pos,Dir,Up){
    m_Source=NULL;
    m_Speed=0.0f;
    m_LifeTime=2.5f;
    m_Velocity={0.0f,0.0f,0.0f};
};
Laser::Laser(Actor* Source):Shot(Source){
    m_Speed=0.0f;
    m_LifeTime=2.5f;
    m_Velocity={0.0f,0.0f,0.0f};
};
Laser::~Laser(){
    this->Destroy();
};
void Laser::Update(float dt){
    m_LifeTime-=dt;
    if(m_LifeTime<=0.0f){
        m_ID=UNKNOWN;
        return ;
    }
    if(m_Source){
        setPosition(m_Source->getPosition());
        setOrientation(m_Source->getDirection(),m_Source->getUp());
    }
};
int Laser::LoadFromFile(){
    return StaticModel::LoadFromFile("Data//Laser.obj");
};
Shot* Laser::Clone(){
    Shot* clone=new Laser();
    clone->DynamicModel::Clone(this);
   clone->setLifeTime(m_LifeTime) ;
    clone->setSource(m_Source);
    clone->setSpeed(m_Speed );
    clone->setDamage(m_Damage) ;
};
void Laser ::Hit(){

};
