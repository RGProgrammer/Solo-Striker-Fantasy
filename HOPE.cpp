#include "HOPE.h"
HOPE::HOPE():Player(){

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
    m_Speed=0.5f;
    return StaticModel::LoadFromFile("Data//ship.obj");
};
void HOPE::Update(float dt){
    m_Pos=AddVertex3d(m_Pos,ScaleVertex3d(m_Velocity,1.0f));
};

void HOPE::Update(SDL_Event* Events, int nbEvents){
    for(int i=0; i<nbEvents;i++){
        if(Events[i].type==SDL_KEYDOWN){
            if(Events[i].key.keysym.sym==SDLK_UP){
                    m_Velocity=AddVertex3d(m_Velocity,ScaleVertex3d(Normalize3d(m_Dir),m_Speed));
            }
            if(Events[i].key.keysym.sym==SDLK_DOWN){
                    m_Velocity=AddVertex3d(m_Velocity,ScaleVertex3d(Normalize3d(m_Dir),-m_Speed));
            }
            if(Events[i].key.keysym.sym==SDLK_RIGHT){
                m_Velocity=AddVertex3d(m_Velocity,ScaleVertex3d(Normalize3d(m_Right),m_Speed));
            }
            if(Events[i].key.keysym.sym==SDLK_LEFT){
                m_Velocity=AddVertex3d(m_Velocity,ScaleVertex3d(Normalize3d(m_Right),-m_Speed));
            }
            if(Events[i].key.keysym.sym==SDLK_x){
                Fire();
            }
            if(Events[i].key.keysym.sym==SDLK_r){
                setPosition({0.0f,0.0f,0.0f});
            }
        }else{
            m_Velocity={0.0f,0.0f,0.0f};
        }
    }
};
void HOPE::Fire(){
    v_Weapons[m_SelectedWeapon]->Fire(m_Scene,m_Pos,m_Dir,m_Up);
};


