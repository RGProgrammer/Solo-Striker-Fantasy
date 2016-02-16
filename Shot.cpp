#include "Shot.h"
Shot::Shot():DynamicModel(),m_Speed(0.0f),m_Source(NULL){
};
Shot::Shot(Vertex3d Pos,Vertex3d Dir,Vertex3d Up ):DynamicModel(Pos,Dir,Up),m_Speed(0.0f),m_Source(NULL){

};
Shot::Shot(Actor* Source):DynamicModel(),m_Speed(0.0f),m_Source(Source){
    //edit shot posiotion and orientation depends on the source
};
Shot::Shot(Shot* clone):DynamicModel(),m_Speed(0.0f),m_Source(NULL){

};
Shot::~Shot(){
    DynamicModel::Destroy();
};
