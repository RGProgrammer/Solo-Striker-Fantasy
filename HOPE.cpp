#include "HOPE.h"
Shooter::Shooter(HOPE* Owner,Vertex3d Trans):DynamicModel(),m_Owner(Owner),m_Trans(Trans),
                              m_nbWeapons(0),m_SelectedWeapon(-1),v_Weapons(NULL){
};
Shooter::~Shooter(){
    this->Destroy();
};
int Shooter::LoadFromFile(){
    v_Weapons=(Weapon**)malloc(sizeof(Weapon*));
    v_Weapons[0]=new MachineGun(NULL);
    v_Weapons[0]->setOwner(this);
    m_nbWeapons=1 ;
    m_SelectedWeapon=0;
    return StaticModel::LoadFromFile("Data//Shooter.obj");
};
void Shooter::Update(float dt){
       setPosition(AddVertex3d(m_Owner->getPosition(),m_Trans));
};
int Shooter::Fire(GameScene* Scene){
    return v_Weapons[m_SelectedWeapon]->Fire(Scene,m_Pos,m_Dir,m_Up);
};
void Shooter::SelectWeapon(int index){
    if(index>=0 && index<m_nbWeapons)
        m_SelectedWeapon=index ;
};
void Shooter::setTransVertex(Vertex3d ver){
    m_Trans=ver ;
};
void Shooter::Destroy(){
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



HOPE::HOPE():Player(),m_MoveDirection({0.0f,0.0f,0.0f}),m_Shooterl(NULL),m_Shooter2(NULL){

};
HOPE::~HOPE(){

};
int HOPE::LoadFromFile() {
    m_Health=1000.0f;
    m_Charge=0 ;
    m_Speed=100.0f;
    m_Shooterl=new Shooter(this,{0.0f,-9.0f,0.f});
    m_Shooter2=new Shooter(this,{0.0f,9.0f,0.f});
    m_Shooterl->LoadFromFile();
    m_Shooter2->LoadFromFile();
    return StaticModel::LoadFromFile("Data//ship.obj");
};
void HOPE::Destroy(){
    if(m_Shooterl){
        delete m_Shooterl;
        m_Shooterl=NULL ;
    }
    if(m_Shooter2){
        delete m_Shooter2;
        m_Shooter2=NULL ;
    }
};
void HOPE::Draw(float* ViewMtx){
    StaticModel::Draw(ViewMtx);
    m_Shooterl->Draw(ViewMtx);
    m_Shooter2->Draw(ViewMtx);
};
void HOPE::Update(float dt){
    if(dt==0)
        dt=0.01f;
    m_Velocity=ScaleVertex3d(m_MoveDirection,m_Speed*dt);
    m_Pos=AddVertex3d(m_Pos,m_Velocity);
    m_Shooterl->Update(dt);
    m_Shooter2->Update(dt);
};

void HOPE::Update(SDL_Event* Events, int nbEvents){
    for(int i=0; i<nbEvents;i++){
        if(Events[i].type==SDL_KEYDOWN){
            if(m_Camera && m_Camera->getViewType()==UP){
                if(Events[i].key.keysym.sym==SDLK_UP){
                    if(!OppositeDirection(m_MoveDirection,m_Dir))
                        m_MoveDirection=Normalize3d(AddVertex3d(m_MoveDirection,m_Dir));
                }
                else if(Events[i].key.keysym.sym==SDLK_DOWN){
                    if(!OppositeDirection(m_MoveDirection,ScaleVertex3d(m_Dir,-1)))
                        m_MoveDirection=Normalize3d(AddVertex3d(m_MoveDirection,ScaleVertex3d(m_Dir,-1)));
                }
                if(Events[i].key.keysym.sym==SDLK_RIGHT){
                    Vertex3d Right=CrossProduct3d(m_Dir,m_Up);
                    if(!OppositeDirection(m_MoveDirection,ScaleVertex3d(Right,-1)))
                        m_MoveDirection=Normalize3d(AddVertex3d(m_MoveDirection,ScaleVertex3d(Right,-1)));
                }
                else if(Events[i].key.keysym.sym==SDLK_LEFT){
                    Vertex3d Right=CrossProduct3d(m_Dir,m_Up);
                    if(!OppositeDirection(m_MoveDirection,Right))
                        m_MoveDirection=Normalize3d(AddVertex3d(m_MoveDirection,Right));
                }
            }else if(m_Camera && m_Camera->getViewType()==SIDE){
                 if(Events[i].key.keysym.sym==SDLK_UP){
                    if(!OppositeDirection(m_MoveDirection,ScaleVertex3d(m_Up,-1)))
                        m_MoveDirection=Normalize3d(AddVertex3d(m_MoveDirection,ScaleVertex3d(m_Up,-1)));
                }
                else if(Events[i].key.keysym.sym==SDLK_DOWN){
                    if(!OppositeDirection(m_MoveDirection,m_Up))
                        m_MoveDirection=Normalize3d(AddVertex3d(m_MoveDirection,m_Up));
                }
                if(Events[i].key.keysym.sym==SDLK_RIGHT){
                     if(!OppositeDirection(m_MoveDirection,m_Dir))
                        m_MoveDirection=Normalize3d(AddVertex3d(m_MoveDirection,m_Dir));
                }
                else if(Events[i].key.keysym.sym==SDLK_LEFT){
                    if(!OppositeDirection(m_MoveDirection,ScaleVertex3d(m_Dir,-1)))
                        m_MoveDirection=Normalize3d(AddVertex3d(m_MoveDirection,ScaleVertex3d(m_Dir,-1)));
                }
            }

            if(Events[i].key.keysym.sym==SDLK_x){
                Fire();
            }
            if(Events[i].key.keysym.sym==SDLK_r){
                setPosition({0.0f,0.0f,0.0f});
            }
            if(Events[i].key.keysym.sym==SDLK_c){
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
        }else{
            m_MoveDirection={0.0f,0.0f,0.0f};
        }
    }
};
void HOPE::Fire(){
    m_Shooterl->Fire(m_Scene);
    m_Shooter2->Fire(m_Scene);
};


