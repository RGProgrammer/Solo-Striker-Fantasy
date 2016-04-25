#include "Explosion.h"
Explosion::Explosion():Effect(),m_MaxScale(2),m_Speed(0.5f){
    m_LifeTime=0.5f ;
};
Explosion::Explosion(Vertex3d Pos):Effect(Pos),m_MaxScale(2),m_Speed(0.5f){
    m_LifeTime=0.5f ;
};
Explosion::Explosion(Vertex3d Pos,Vertex3d Dir, Vertex3d Up):Effect(Pos,Dir,Up),
                                                            m_MaxScale(2),m_Speed(0.5f){
    m_LifeTime=0.5f ;
};
Explosion::Explosion(Actor* Source):Effect(Source),m_MaxScale(2),m_Speed(0.5f){
    m_LifeTime=0.5f ;
};
void Explosion::Update(float dt){
    m_LifeTime-=dt;
    if(m_Scale<m_MaxScale){
        m_Scale+=m_Speed*dt;
    }
    if(m_LifeTime<= 0.0f){
        m_Stat=DONE ;
    }
};
