#include "Enemy.h"
Enemy::Enemy():DynamicModel(),m_nbActions(0),v_Actions(NULL),m_Scene(NULL){
    m_ID|=ENEMY ;
};
Enemy::Enemy(Vertex3d Pos):DynamicModel(Pos),m_nbActions(0),v_Actions(NULL),m_Scene(NULL){
   m_ID|=ENEMY ;};
Enemy::Enemy(Vertex3d Pos,Vertex3d Dir,Vertex3d Up):DynamicModel(Pos,Dir,Up),m_nbActions(0),v_Actions(NULL),m_Scene(NULL){
    m_ID|=ENEMY ;};
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
    if(v_Actions==NULL){
        v_Actions=(Action*)malloc((m_nbActions+1)*sizeof(Action));
        if(v_Actions==NULL)
            return 0 ;
    }else{
        Action* tmp=(Action*)malloc((m_nbActions+1)*sizeof(Action));
        if(tmp==NULL)
            return 0 ;
        for(int i=0; i<m_nbActions;i++)
            tmp[i]=v_Actions[i] ;
        free(v_Actions);
        v_Actions=tmp;
    }
    v_Actions[m_nbActions]=action ;
    m_nbActions++;
    return 1 ;
};
