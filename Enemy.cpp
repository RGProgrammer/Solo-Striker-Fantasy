#include "Enemy.h"
Enemy::Enemy():DynamicModel(),m_nbActions(0),v_Actions(NULL),m_Scene(NULL){
    StaticModel::m_ID|=ENEMY ;
};
Enemy::Enemy(Vertex3d Pos):DynamicModel(Pos),m_nbActions(0),v_Actions(NULL),m_Scene(NULL){
    StaticModel::m_ID|=ENEMY ;};
Enemy::Enemy(Vertex3d Pos,Vertex3d Dir,Vertex3d Up):DynamicModel(Pos,Dir,Up),m_nbActions(0),v_Actions(NULL),m_Scene(NULL){
    StaticModel::m_ID|=ENEMY ;};
Enemy::~Enemy(){
    this->Destroy();
};
void Enemy::setScene(GameScene* Scene){
    m_Scene=Scene;
};
void Enemy::Destroy(){
    DynamicModel::Destroy();
    m_Scene=NULL;
    if(v_Actions){
        free(v_Actions);
        v_Actions=NULL ;
    }
    m_nbActions=0;
};
int Enemy::addAction(Action action){
    return 0 ;
};
