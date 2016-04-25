#include "Effect.h"
Effect::Effect():Effect({0.0f,0.0f,0.0f}){
};
Effect::Effect(Vertex3d Pos): Effect(Pos,{0.0f,0.0f,1.0f},{0.0f,1.0f,0.0f}){
};
Effect::Effect(Vertex3d Pos, Vertex3d Dir, Vertex3d Up):DynamicModel(Pos,Dir,Up),
                                                        m_Stat(NOTSTARTED),m_LifeTime(0.0f),
                                                        m_Source(NULL){
};
Effect::Effect(Actor* Source):Effect(){
    m_Source=Source ;
    this->m_Pos=Source->getPosition();
};
void Effect::Draw(float* ViewMtx){
    if(m_Stat==STARTED){
        DynamicModel::Draw(ViewMtx);
    }
};
void Effect::Start(){
    m_Stat=STARTED ;
    if(m_Source){
        this->setPosition(m_Source->getPosition());
    }
};
void Effect::Stop() {
    m_Stat=DONE ;
};
bool Effect::isStarted(){
    return (m_Stat==STARTED)?true : false ;
};
bool Effect::isDone(){
    return (m_Stat==DONE)? true : false ;
};
