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
int Explosion::LoadFromFile(){
    Sound* Effect=NULL ;
    Effect=SoundEngine::LoadWAVFile("Sound//explosion.wav");
    if(Effect){
        m_Sound=getGlobalSoundEngineInstance()->LoadSound(*Effect);
        free(Effect->Buffer);
        free(Effect);
        Effect=NULL;
    }
    return StaticModel::LoadFromFile("Data//Explosion.obj");
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
