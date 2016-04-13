#include "Enemy.h"
Enemy::Enemy():DynamicModel(),m_nbActions(0),v_Actions(NULL),m_Scene(NULL),m_CurrentActions(0),
                        m_Health(1),m_Stat(ALIVE),m_Dt(0),m_Sample(NULL){
    m_ID|=ENEMY | PHYSICAL ;
};
Enemy::Enemy(Vertex3d Pos):DynamicModel(Pos),m_nbActions(0),v_Actions(NULL),m_Scene(NULL),m_CurrentActions(0),m_Health(1),
                                m_Stat(ALIVE),m_Dt(0),m_Sample(NULL){
   m_ID|=ENEMY | PHYSICAL ;};
Enemy::Enemy(Vertex3d Pos,Vertex3d Dir,Vertex3d Up):DynamicModel(Pos,Dir,Up),m_nbActions(0),v_Actions(NULL),m_Scene(NULL),
                                                    m_CurrentActions(0),m_Health(1),m_Stat(ALIVE),m_Dt(0),m_Sample(NULL){
    m_ID|=ENEMY | PHYSICAL ;};
Enemy::~Enemy(){
    this->Destroy();
};
void Enemy::Draw(float* ViewMtx){
    if(m_Stat !=DEAD)
        StaticModel::Draw(ViewMtx);
};
void Enemy::Update(float dt){
    if(m_Stat!=DEAD){
        bool verif=false ;
        if(dt==0.0f)
            dt=0.01f;
        m_Dt+=dt;
        ///update actions here
        if(v_Actions){
            for(int i=m_CurrentActions;v_Actions[i].Instance-m_Dt<=0.0f;i++){
                m_CurrentActions=i;
                verif=true;
                if(v_Actions[i].ActionType==EXPLODE)
                    Explode();
                else if(v_Actions[i].ActionType==MOVEACTION){
                    m_Velocity=AddVertex3d(m_Velocity,ScaleVertex3d(Normalize3d(((Movement*)(v_Actions[i].Data))->Translate),((Movement*)(v_Actions[i].Data))->Speed*m_Dt));
                }else if(v_Actions[i].ActionType==FIREACTION){
                    if(v_Actions[i].Data){
                        Fire(*((Vertex3d*)(v_Actions[i].Data)));
                    }else{
                        Fire(m_Dir);
                    }
                }
            }
            m_Pos=AddVertex3d(m_Pos,m_Velocity);
            if(verif)
                m_Dt=0.0f;
        }
    }else{
        m_ID=UNKNOWN ;
    }
};
void Enemy::setScene(GameScene* Scene){
    m_Scene=Scene;
};
void Enemy::Destroy(){
    DynamicModel::Destroy();
    m_Scene=NULL;
    if(v_Actions){
        for(int i=0;i<m_nbActions;i++)
            if(v_Actions[i].Data)
                free(v_Actions[i].Data);
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
int Enemy::Fire(Vertex3d Direction){
    /*if(m_Sample){
        Shot* Clone=NULL;
        m_Scene->AddActor()
    }*/
};
void Enemy::Explode(){
    printf("Explode \n");
    m_Stat=DEAD ;
};
void Enemy::getDamage(int damage){
    if(m_Stat==ALIVE){
        m_Health-=damage;
        if(m_Health<=0){
            m_Stat=DEAD;
            m_ID=UNKNOWN;}
    }
};
