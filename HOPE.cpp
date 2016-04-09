#include "HOPE.h"
HOPE::HOPE():Player(),m_MoveDirection({0.0f,0.0f,0.0f}){

};
HOPE::~HOPE(){

};
int HOPE::LoadFromFile() {
    m_Health=1000.0f;
    m_Charge=0 ;
    v_Weapons=(Weapon**)malloc(sizeof(Weapon*));
    v_Weapons[0]=new MachineGun(NULL);
    v_Weapons[0]->setOwner(this);
    m_nbWeapons=1 ;
    m_SelectedWeapon=0;
    m_Speed=100.0f;
    return StaticModel::LoadFromFile("Data//ship.obj");
};
void HOPE::Update(float dt){
    if(dt==0)
        dt=0.01f;
    m_Velocity=ScaleVertex3d(m_MoveDirection,m_Speed*dt);
    m_Pos=AddVertex3d(m_Pos,m_Velocity);
};

void HOPE::Update(SDL_Event* Events, int nbEvents){
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
                Fire();
            }
            if(Events[i].key.keysym.sym==SDLK_r){
                setPosition({0.0f,0.0f,0.0f});
            }
            if(Events[i].key.keysym.sym==SDLK_c){
                if(m_Camera->getViewType()==SIDE){
                    m_Camera->setViewType(UP);
                    m_Pos.y=0.0f ;
                }
                else{
                    m_Camera->setViewType(SIDE);
                    m_Pos.x=0.0f;
                }
            }
            printf("player position: %f %f %f\n",m_Pos.x,m_Pos.y,m_Pos.z);
        }else{
            m_MoveDirection={0.0f,0.0f,0.0f};
        }
    }
};
void HOPE::Fire(){
    v_Weapons[m_SelectedWeapon]->Fire(m_Scene,m_Pos,m_Dir,m_Up);
};


