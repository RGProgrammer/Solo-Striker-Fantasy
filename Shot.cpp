#include "Shot.h"
Shot::Shot():DynamicModel(),m_Speed(0.0f),m_Source(NULL){
    setColor({1.0f,0.0f,0.0f});
};
Shot::Shot(Vertex3d Pos,Vertex3d Dir,Vertex3d Up ):DynamicModel(Pos,Dir,Up),m_Speed(0.0f),m_Source(NULL){
    setColor({1.0f,0.0f,0.0f});
};
Shot::Shot(Actor* Source):DynamicModel(),m_Speed(0.0f),m_Source(Source){
    //edit shot posiotion and orientation depends on the source
    setColor({1.0f,0.0f,0.0f});
};
Shot::Shot(Shot* clone):DynamicModel(),m_Speed(0.0f),m_Source(NULL){
    this->Clone(clone);
    setColor({1.0f,0.0f,0.0f});
};
Shot::~Shot(){
    DynamicModel::Destroy();
};
int Shot::Clone(Shot* clone){
    StaticModel::Clone(clone);
    m_Source=clone->m_Source;
    m_Speed=clone->m_Speed;
    m_Damage=clone->m_Damage;
};
