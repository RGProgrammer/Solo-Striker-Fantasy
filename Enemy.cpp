#include "Enemy.h"
Enemy::Enemy():Enemy({0.0f,0.0f,0.0f}){
};
Enemy::Enemy(Vertex3d Pos):Enemy(Pos,{0.0f,0.0f,-1.0f},{0.0f,1.0f,0.0f}){
};
Enemy::Enemy(Vertex3d Pos,Vertex3d Dir,Vertex3d Up):DynamicModel(Pos,Dir,Up),m_nbActions(0),v_Actions(NULL),m_Scene(NULL),
                                                    m_CurrentActions(0),m_Health(1),m_Stat(ALIVE),m_Dt(0),m_Sample(NULL),
                                                    m_Explosion(NULL),m_Active(false),m_EnemyHitSound(0){
    m_ID|=ENEMY | PHYSICAL ;
    m_LastPostion=m_Pos ;
    Sound* effect=SoundEngine::LoadWAVFile("Sound//hit.wav");
    if(effect){
        m_EnemyHitSound=getGlobalSoundEngineInstance()->LoadSound(*effect);
        free(effect->Buffer);
        free(effect);
    }
};
Enemy::~Enemy(){
    this->Destroy();
};
void Enemy::Draw(float* ViewMtx){
    if(m_Stat !=DEAD && m_Stat != EXPLODING && m_Active)
        StaticModel::Draw(ViewMtx);
    else if(m_Stat==EXPLODING)
        m_Explosion->Draw(ViewMtx);
};
void Enemy::Update(float dt){
    if(m_Stat!=DEAD && m_Stat!=EXPLODING){
        m_Dt+=dt;
        ///update actions here
        if(v_Actions && m_CurrentActions < m_nbActions){
            if(v_Actions[m_CurrentActions].Instance-m_Dt>=0 )
                return ;
            else
                m_Active=true ;
            if(v_Actions[m_CurrentActions].ActionType==KILL){
                this->Kill();
                return ;
            }else if(v_Actions[m_CurrentActions].ActionType==EXPLODE){
                    Explode();
                }
            else if(v_Actions[m_CurrentActions].ActionType==MOVEACTION){
                m_Velocity=ScaleVertex3d(Normalize3d(getVertex3d(m_Pos,((Movement*)(v_Actions[m_CurrentActions].Data))->Translate)),((Movement*)(v_Actions[m_CurrentActions].Data))->Speed*dt);
                if(Distance3d(m_LastPostion,m_Pos)>=Distance3d(m_LastPostion,((Movement*)(v_Actions[m_CurrentActions].Data))->Translate)){
                        m_Pos=((Movement*)(v_Actions[m_CurrentActions].Data))->Translate ;
                        m_Velocity={0.0f,0.0f,0.0f};
                        m_LastPostion=m_Pos;
                        m_CurrentActions++;
                        m_Dt=0.0f;
                }
            }else if(v_Actions[m_CurrentActions].ActionType==FIREACTION){
                if(v_Actions[m_CurrentActions].Data==NULL)
                    Fire();
                else{
                    Fire(((Vertex3d*)(v_Actions[m_CurrentActions].Data))[0],
                         ((Vertex3d*)(v_Actions[m_CurrentActions].Data))[1]);
                }
                m_CurrentActions++;
                m_Dt=0.0f;
            }else{
                if(v_Actions[m_CurrentActions].ActionType==ATTACK){
                    if(m_Pos.z<(-100.0f)){
                        m_CurrentActions++;
                    }
                    Vertex3d player_pos=m_Scene->getPlayer()->getPosition();
                    if(m_Pos.z >= player_pos.z){
                        m_Velocity=AddVertex3d(ScaleVertex3d(Normalize3d(m_Dir),70.0f*dt),ScaleVertex3d(Normalize3d(SubsVertex3d(player_pos,m_Pos)),30.0f*dt));
                    }else{
                        m_Velocity=ScaleVertex3d(Normalize3d(m_Dir),150.0f*dt);
                    }
                }
                m_Dt=0.0f;
            }
            m_Pos=AddVertex3d(m_Pos,m_Velocity);
        }
    }else if (m_Stat==EXPLODING){
        if(!m_Explosion->isDone()){
            m_Explosion->Update(dt);
        }else{
            m_Stat=DEAD;
            m_ID=UNKNOWN ;}
    }
};
bool Enemy::isActive(){
    return m_Active;
};
void Enemy::setActive(bool a){
    m_Active=a ;
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
    if(m_Explosion){
        m_Explosion->Destroy();
        delete m_Explosion ;
        m_Explosion=NULL ;
    }
    if(m_Sample){
        m_Sample->Destroy();
        delete m_Sample ;
        m_Sample=NULL ;
    }
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
int Enemy::Fire(){
    if(m_Sample){
        Shot* ShotClone=NULL ;
        ShotClone=m_Sample->Clone();
        ShotClone->setPosition(m_Pos);
        ShotClone->setOrientation(m_Dir,m_Up);
        ShotClone->setSource(this);
        if(!ShotClone)
            return 0 ;
        m_Scene->AddActor(ShotClone);
    }
    return 1;
};
int Enemy::Fire(Vertex3d Dir, Vertex3d Up){
    if(m_Sample){
        Shot* ShotClone=NULL ;
        ShotClone=m_Sample->Clone();
        ShotClone->setPosition(m_Pos);
        ShotClone->setOrientation(Dir,Up);
        ShotClone->setSource(this);
        if(!ShotClone)
            return 0 ;
        m_Scene->AddActor(ShotClone);
    }
    return 1;
}
void Enemy::addShotSample(Shot* Sample){
    m_Sample=Sample;
};
void Enemy::Explode(){
    m_Active=false ;
    m_Stat=EXPLODING;
    m_Explosion->Start();
    m_Health=0 ;
};
void Enemy::getDamage(int damage){
    if(m_Stat==ALIVE){
        getGlobalSoundEngineInstance()->PlaySound(m_EnemyHitSound,this);
        m_Health-=damage;
        if(m_Health<=0){
            this->Explode();
        }
    }
};
void Enemy::Kill(){
    m_Stat=DEAD;
    m_ID=UNKNOWN ;
};
