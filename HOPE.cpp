#include "HOPE.h"
Shooter::Shooter(HOPE* Owner,Vertex3d Trans):DynamicModel(),m_Owner(Owner),m_Trans(Trans),
                              m_nbWeapons(0),m_SelectedWeapon(-1),v_Weapons(NULL),m_SwitchSound(0){
    m_ID|=PLAYER ;
};
Shooter::~Shooter(){
    this->Destroy();
};
int Shooter::LoadFromFile(){
    v_Weapons=(Weapon**)malloc(3*sizeof(Weapon*));
    v_Weapons[0]=new MachineGun(NULL);
    v_Weapons[0]->setOwner(this);
    v_Weapons[1]=new Rampage(NULL);
    v_Weapons[1]->setOwner(this);
    v_Weapons[2]=new EnemyChaserLauncher(NULL);
    v_Weapons[2]->setOwner(this);
    m_nbWeapons=3 ;
    m_SelectedWeapon=0;
    Sound* sound=SoundEngine::LoadWAVFile("Sound//weaponselect.wav");
    if(sound){
        m_SwitchSound=getGlobalSoundEngineInstance()->LoadSound(*sound);
        free(sound->Buffer);
        free(sound);
    }
    return StaticModel::LoadFromFile("Data//Shooter.obj");
};
void Shooter::Update(float dt){
        m_Trans=Rotate3d(m_Trans,m_Dir,3.5f*dt);
       setPosition(AddVertex3d(m_Owner->getPosition(),m_Trans));
};
int Shooter::Fire(float dt,GameScene* Scene){
    return v_Weapons[m_SelectedWeapon]->Fire(dt,Scene,m_Pos,m_Dir,m_Up);
};
void Shooter::SelectWeapon(int index){
    if(index>0 && index<=m_nbWeapons){
        m_SelectedWeapon=index-1 ;
        getGlobalSoundEngineInstance()->PlaySound(m_SwitchSound,this);
    }
};
int Shooter::getSelectedWeapon(){
    return m_SelectedWeapon+1 ;
};
Weapon* Shooter::getSelectedWeaponObj(){
    return v_Weapons[m_SelectedWeapon];
};
void Shooter::setTransVertex(Vertex3d ver){
    m_Trans=ver ;
};
void Shooter::Destroy(){
    DynamicModel::Destroy();
    m_Owner=NULL ;
    if(v_Weapons){
        for(int i=0;i<m_nbWeapons;i++){
            delete v_Weapons[i];
        }
        free(v_Weapons);
        v_Weapons=NULL ;
    }
    m_nbWeapons=0;
    m_SelectedWeapon=-1;
};


HOPE::HOPE():Player(),m_MoveDirection({0.0f,0.0f,0.0f}),m_Shooterl(NULL),m_Shooter2(NULL),m_Firing(false),
            m_GStatus(NULL),m_CreditHandler(NULL),m_GameOver(NULL){

};
HOPE::~HOPE(){
    this->Destroy();
};
int HOPE::LoadFromFile() {
    m_Charge=0 ;
    m_Speed=50.0f;
    m_Shooterl=new Shooter(this,{0.0f,-9.0f,0.f});
    m_Shooter2=new Shooter(this,{0.0f,9.0f,0.f});
    m_Shooterl->LoadFromFile();
    m_Shooter2->LoadFromFile();
    m_Score=new ScoreHandler();
    m_Score->LoadFromFile();
    m_GStatus=new PlayerStatus;
    m_GStatus->LoadFromFile();
    m_GStatus->setIcon(m_Shooterl->getSelectedWeaponObj()->getIcon());
    m_CreditHandler=new CreditHandler();
    m_CreditHandler->Init(3);
    m_GameOver=new StaticModel();
    m_GameOver->LoadFromFile("Data//GameOver.obj");
    m_GameOver->setPosition({0.0f,0.0f,-10.0f});
    m_Stat=ALIVE ;
    return StaticModel::LoadFromFile("Data//ship.obj");
};
void HOPE::Destroy(){
    Player::Destroy();
    if(m_Shooterl){
        delete m_Shooterl;
        m_Shooterl=NULL ;
    }
    if(m_Shooter2){
        delete m_Shooter2;
        m_Shooter2=NULL ;
    }
    if(m_GStatus){
        m_GStatus->Destroy();
        delete m_GStatus;
        m_GStatus=NULL ;
    }
    if(m_CreditHandler){
        m_CreditHandler->Destroy();
        delete m_CreditHandler ;
        m_CreditHandler=NULL;
    }
    if(m_GameOver){
        m_GameOver->Destroy();
        delete m_GameOver ;
        m_GameOver=NULL ;
    }
};
void HOPE::Init(){
    m_Stat=ALIVE;
    m_Score->setValue(0);
    m_CreditHandler->setCreditValue(3);
    m_GStatus->setShieldValue(3);
};
void HOPE::Draw(float* ViewMtx){
    if(m_Stat!= DEAD){
        m_Score->Draw(NULL);
        m_GStatus->Draw(NULL);
        StaticModel::Draw(ViewMtx);
        m_Shooterl->Draw(ViewMtx);
        m_Shooter2->Draw(ViewMtx);
        if(m_Stat==CHECK){
            m_CreditHandler->Draw(NULL);
        }
    }else{
        m_GameOver->Draw(NULL);
    }
};
void HOPE::Update(float dt){
    if(m_Stat== ALIVE){
        m_Velocity=ScaleVertex3d(m_MoveDirection,m_Speed*dt);
        m_Pos=AddVertex3d(m_Pos,m_Velocity);
        m_Shooterl->Update(dt);
        m_Shooter2->Update(dt);
        if(m_Firing==true)
            Fire(dt);
    }else if(m_Stat== HIT){
        m_Dt-=dt ;
        if(m_Dt<=0)
            m_Stat=ALIVE;
    }
};

void HOPE::Update(SDL_Event* Events, int nbEvents){
    if(m_Stat==ALIVE)
    for(int i=0; i<nbEvents;i++){
        if(Events[i].type==SDL_KEYDOWN){
            if(m_Camera && m_Camera->getViewType()==UP){
                if(Events[i].key.keysym.sym==SDLK_UP){
                        m_MoveDirection=Normalize3d(AddVertex3d(m_MoveDirection,m_Dir));
                }
                else if(Events[i].key.keysym.sym==SDLK_DOWN){
                        m_MoveDirection=Normalize3d(AddVertex3d(m_MoveDirection,ScaleVertex3d(m_Dir,-1)));
                }
                if(Events[i].key.keysym.sym==SDLK_RIGHT){
                    Vertex3d Right=CrossProduct3d(m_Dir,m_Up);
                        m_MoveDirection=Normalize3d(AddVertex3d(m_MoveDirection,ScaleVertex3d(Right,-1)));
                }
                else if(Events[i].key.keysym.sym==SDLK_LEFT){
                    Vertex3d Right=CrossProduct3d(m_Dir,m_Up);
                        m_MoveDirection=Normalize3d(AddVertex3d(m_MoveDirection,Right));
                }
            }else if(m_Camera && m_Camera->getViewType()==SIDE){
                 if(Events[i].key.keysym.sym==SDLK_UP){
                        m_MoveDirection=Normalize3d(AddVertex3d(m_MoveDirection,ScaleVertex3d(m_Up,-1)));
                }
                else if(Events[i].key.keysym.sym==SDLK_DOWN){
                        m_MoveDirection=Normalize3d(AddVertex3d(m_MoveDirection,m_Up));
                }
                if(Events[i].key.keysym.sym==SDLK_RIGHT){
                        m_MoveDirection=Normalize3d(AddVertex3d(m_MoveDirection,m_Dir));
                }
                else if(Events[i].key.keysym.sym==SDLK_LEFT){
                        m_MoveDirection=Normalize3d(AddVertex3d(m_MoveDirection,ScaleVertex3d(m_Dir,-1)));
                }
            }

            if(Events[i].key.keysym.sym==SDLK_x){
                if(m_Shooterl->getSelectedWeapon()!=1){
                    m_Shooterl->SelectWeapon(1);
                    m_Shooter2->SelectWeapon(1);
                    m_GStatus->setIcon(m_Shooterl->getSelectedWeaponObj()->getIcon());
                }
                m_Firing=true ;
            }
            if(Events[i].key.keysym.sym==SDLK_z){
                if(m_Shooterl->getSelectedWeapon()!=2){
                    m_Shooterl->SelectWeapon(2);
                    m_Shooter2->SelectWeapon(2);
                    m_GStatus->setIcon(m_Shooterl->getSelectedWeaponObj()->getIcon());
                }
                m_Firing=true ;
            }
            if(Events[i].key.keysym.sym==SDLK_c){
                if(m_Shooterl->getSelectedWeapon()!=3){
                    m_Shooterl->SelectWeapon(3);
                    m_Shooter2->SelectWeapon(3);
                    m_GStatus->setIcon(m_Shooterl->getSelectedWeaponObj()->getIcon());
                }
                m_Firing=true ;
            }
            if(Events[i].key.keysym.sym==SDLK_r){
                setPosition({0.0f,0.0f,0.0f});
                m_MoveDirection={0.0f,0.0f,0.0f};
            }
            if(Events[i].key.keysym.sym==SDLK_v){
                if(m_Camera->getViewType()==SIDE){
                    m_Camera->setViewType(UP);
                    m_Shooterl->setTransVertex({-11.0f,0.0f,0.0f});
                    m_Shooter2->setTransVertex({11.0f,0.0f,0.0f});
                    m_Pos.y=0.0f ;
                }
                else{
                    m_Camera->setViewType(SIDE);
                    m_Shooterl->setTransVertex({0.0f,-9.0f,0.0f});
                    m_Shooter2->setTransVertex({0.0f,9.0f,0.0f});
                    m_Pos.x=0.0f;
                }
            }
        }else if(Events[i].type==SDL_KEYUP){
            m_MoveDirection={0.0f,0.0f,0.0f};
            if(Events[i].key.keysym.sym==SDLK_x ||
               Events[i].key.keysym.sym==SDLK_z ||
               Events[i].key.keysym.sym==SDLK_c)
                m_Firing=false ;
        }
    }
    else if(m_Stat==CHECK){
        if(Events[0].type==SDL_KEYDOWN)
            if(Events[0].key.keysym.sym==SDLK_z){
                m_CreditHandler->MinusOne();
                m_GStatus->setShieldValue(3);
                m_Stat=ALIVE ;
            }else if(Events[0].key.keysym.sym==SDLK_x){
                m_Stat=DEAD;
            }
    }
};
void HOPE::Fire(float dt){
    m_Shooterl->Fire(dt,m_Scene);
    m_Shooter2->Fire(dt,m_Scene);
};
void HOPE::getDamage(){
    if(m_Stat==ALIVE){
        if(m_GStatus->getShieldValue()==0){
            if(m_CreditHandler->getCredit()==0)
                m_Stat=DEAD ;
            else
                m_Stat=CHECK;
        }else {
            m_GStatus->setShieldValue(m_GStatus->getShieldValue()-1);
            m_Stat=HIT;
            m_Dt=2.0f;
        }
    }
};
