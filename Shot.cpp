#include "Shot.h"
Shot::Shot():DynamicModel(),m_Speed(0.0f),m_Source(NULL),m_LifeTime(0.0f){
    m_ID|= SHOT |PHYSICAL ;
    setColor({1.0f,0.0f,0.0f});
};
Shot::Shot(Vertex3d Pos,Vertex3d Dir,Vertex3d Up ):DynamicModel(Pos,Dir,Up),m_Speed(0.0f),m_Source(NULL),m_LifeTime(0.0f){
    m_ID|= SHOT |PHYSICAL ;
    setColor({1.0f,0.0f,0.0f});
};
Shot::Shot(Actor* Source):DynamicModel(),m_Speed(0.0f),m_Source(Source),m_LifeTime(0.0f){
    m_ID|= SHOT |PHYSICAL ;
    //edit shot posiotion and orientation depends on the source
    setColor({1.0f,0.0f,0.0f});
};
Shot::Shot(Shot* clone):DynamicModel(),m_Speed(0.0f),m_Source(NULL),m_LifeTime(0.0f){
    this->Clone(clone);
    setColor({1.0f,0.0f,0.0f});
};
Shot::~Shot(){
};
int Shot::Clone(Shot* clone){
    StaticModel::Clone(clone);
    m_Source=clone->m_Source;
    m_Speed=clone->m_Speed;
    m_Damage=clone->m_Damage;
};
void Shot::setSource(Actor* Source){
    m_Source=Source ;
};
void Shot::setSpeed(float Speed){
    m_Speed=Speed ;
};
void Shot::setDamage(int Damage){
    m_Damage=Damage;
};
Actor* Shot::getSource(){
    return m_Source ;
};
int    Shot::getDamage(){
    return m_Damage ;
};
void Shot::Hit(){
    m_Speed=0.0f;
    m_Velocity={0.0f,0.0f,0.0f};
    m_ID=UNKNOWN;
};
