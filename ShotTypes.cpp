#include "ShotTypes.h"

EnergyBullet::EnergyBullet():Shot(){
    m_Damage=5 ;
    m_Source=NULL;
    m_Speed=150.0f;
    m_LifeTime=10.0f;
    setColor({0.98f,0.73f,0.16f});
};
EnergyBullet::EnergyBullet(Vertex3d Pos,Vertex3d Dir,Vertex3d Up):Shot(Pos,Dir,Up){
    m_Damage=5 ;
    m_Source=NULL;
    m_Speed=150.0f;
    m_LifeTime=10.0f;
    setColor({0.98f,0.73f,0.16f});
};
EnergyBullet::EnergyBullet(Actor* Source):Shot(Source){
    m_Damage=5 ;
    m_Speed=150.0f;
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
    return clone ;
};
void EnergyBullet::Hit(){
    m_Speed=0.0f;
    m_Velocity={0.0f,0.0f,0.0f};
    m_ID=UNKNOWN;
};
//EnemyChaser
EnemyChaser::EnemyChaser():Shot(),m_Target(NULL){
    m_Damage=5 ;
    m_Source=NULL;
    m_Speed=100.0f;
    m_LifeTime=10.0f;
    setColor({0.0f,0.0f,1.0f});
};
EnemyChaser::EnemyChaser(Vertex3d Pos,Vertex3d Dir,Vertex3d Up): Shot(Pos,Dir,Up),m_Target(NULL){
    m_Damage=5 ;
    m_Source=NULL;
    m_Speed=100.0f;
    m_LifeTime=10.0f;
    setColor({0.0f,0.0f,1.0f});
};
EnemyChaser::EnemyChaser(Actor* Source):Shot(Source),m_Target(NULL){
    m_Damage=5 ;
    m_Source=NULL;
    m_Speed=100.0f;
    m_LifeTime=10.0f;
    setColor({0.0f,0.0f,1.0f});
};
EnemyChaser::~EnemyChaser(){
    Destroy();
};
void EnemyChaser::Update(float dt){
    /// this code need to be changed

    m_LifeTime-=dt;
    m_Velocity=ScaleVertex3d(m_Dir,m_Speed*dt);
    m_Pos=AddVertex3d(m_Pos,m_Velocity);
    if(Magnitude3d(SubsVertex3d({0.0f,0.0f,0.0f},m_Pos))>250.0f ||
       m_LifeTime<=0 || !(m_Target->getID()& ENEMY))
        m_ID=UNKNOWN ;
};
int EnemyChaser::LoadFromFile(){
    return StaticModel::LoadFromFile("Data//EnemyChaser.obj");
};
Shot* EnemyChaser::Clone(){
    Shot* clone=new EnemyChaser();
    clone->DynamicModel::Clone(this);
    clone->setLifeTime(m_LifeTime) ;
    clone->setSource(m_Source);
    clone->setSpeed(m_Speed );
    clone->setDamage(m_Damage) ;
    return clone ;
};
void EnemyChaser::Hit(){
    m_Speed=0.0f;
    m_Velocity={0.0f,0.0f,0.0f};
    m_ID=UNKNOWN;
};
void EnemyChaser::setTarget(Actor* Target){
    m_Target=Target;
};
//Rampage Shot
RampageShot::RampageShot():Shot(){
    m_Damage=5 ;
    m_Source=NULL;
    m_Speed=150.0f;
    m_LifeTime=10.0f;
    setColor({1.0f,0.0f,0.0f});
};
RampageShot::RampageShot(Vertex3d Pos,Vertex3d Dir,Vertex3d Up):Shot(Pos,Dir,Up){
    m_Damage=5 ;
    m_Source=NULL;
    m_Speed=150.0f;
    m_LifeTime=10.0f;
    setColor({1.0f,0.0f,0.0f});
};
RampageShot::RampageShot(Actor* Source):Shot(Source){
    m_Damage=5 ;
    m_Speed=150.0f;
    m_LifeTime=100.0f;
    setColor({1.0f,0.0f,0.0f});
};
RampageShot::~RampageShot(){
};
void RampageShot::Update(float dt){
    m_LifeTime-=dt;
    m_Velocity=ScaleVertex3d(m_Dir,m_Speed*dt);
    m_Pos=AddVertex3d(m_Pos,m_Velocity);
    if(Magnitude3d(SubsVertex3d({0.0f,0.0f,0.0f},m_Pos))>250.0f || m_LifeTime<=0)
        m_ID=UNKNOWN ;
};
int RampageShot::LoadFromFile(){
    return StaticModel::LoadFromFile("Data//RampageShot.obj");
};
Shot* RampageShot::Clone(){
    Shot* clone=new RampageShot();
    clone->DynamicModel::Clone(this);
    clone->setLifeTime(m_LifeTime) ;
    clone->setSource(m_Source);
    clone->setSpeed(m_Speed );
    clone->setDamage(m_Damage) ;
    return clone ;
};
void RampageShot::Hit(){
    m_Speed=0.0f;
    m_Velocity={0.0f,0.0f,0.0f};
    m_ID=UNKNOWN;
};


SmallShot::SmallShot():Shot(){
    m_Source=NULL;
    m_Speed=20.0f;
    m_LifeTime=15.0f;
    m_Velocity=ScaleVertex3d(Normalize3d(StaticModel::m_Dir),m_Speed);
    this->setColor({0.929f,0.262f,0.937f});
};
SmallShot::SmallShot(Vertex3d Pos,Vertex3d Dir,Vertex3d Up):Shot(Pos,Dir,Up){
    m_Source=NULL;
    m_Speed=20.0f;
    m_LifeTime=15.0f;
    m_Velocity=ScaleVertex3d(Normalize3d(StaticModel::m_Dir),m_Speed);
    this->setColor({0.929f,0.262f,0.937f});
};
SmallShot::SmallShot(Actor* Source):Shot(){
    m_Source=Source;
    m_Speed=20.0f;
    m_LifeTime=10.0f;
    this->setColor({0.929f,0.262f,0.937f});
};
SmallShot::~SmallShot(){
};
void SmallShot::Update(float dt){
    if(dt==0)
        dt=0.1f;
    m_Dt+=dt;
    if(m_Dt>=m_LifeTime)
        m_ID=UNKNOWN ;
    m_Velocity=ScaleVertex3d(Normalize3d(StaticModel::m_Dir),m_Speed);
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
    return clone ;
};
void SmallShot::Hit(){
    m_Speed=0.0f;
    m_Velocity={0.0f,0.0f,0.0f};
    m_ID=UNKNOWN;
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
    return clone;
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
    return clone;
};
void Laser ::Hit(){

};
