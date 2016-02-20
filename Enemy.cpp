#include "Enemy.h"
Enemy::Enemy():DynamicModel(),m_nbBehaviours(0),v_Behaviours(NULL),m_Scene(NULL){};
Enemy::Enemy(Vertex3d Pos):DynamicModel(Pos),m_nbBehaviours(0),v_Behaviours(NULL),m_Scene(NULL){};
Enemy::Enemy(Vertex3d Pos,Vertex3d Dir,Vertex3d Up):DynamicModel(Pos,Dir,Up),m_nbBehaviours(0),v_Behaviours(NULL),m_Scene(NULL){};
Enemy::~Enemy(){
    this->Destroy();
};
void Enemy::setScene(GameScene* Scene){
    m_Scene=Scene;
};
void Enemy::Destroy(){
    DynamicModel::Destroy();
    m_Scene=NULL;
    if(v_Behaviours){
        free(v_Behaviours);
        v_Behaviours=NULL ;
    }
    m_nbBehaviours=0;
};
int Enemy::addBehaviour(Behaviour behav){
    return 0 ;
};
