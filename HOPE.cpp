#include "HOPE.h"
HOPE::HOPE():Player(){

};
HOPE::~HOPE(){

};
int HOPE::LoadFromFile() {
    m_Health=1000.0f;
    m_Charge=0 ;
    v_Weapons=(Weapon**)malloc(sizeof(Weapon*));
    v_Weapons[0]=new MachineGun((StaticModel*)this);
    m_nbWeapons=1 ;
    m_SelectedWeapon=0;
    m_Speed=1.2f;
    return StaticModel::LoadFromFile("model.obj");
};
void HOPE::Update(float dt){
    StaticModel::m_Pos=AddVertex3d(StaticModel::m_Pos,ScaleVertex3d(m_Velocity,dt));
};
void HOPE::Update(SDL_Event* Events,int nbEvents){
    for(int i=0;i<nbEvents;i++)
        if(Events[i].type==SDL_KEYDOWN){
            if(Events[i].key.keysym.sym==SDLK_UP){
                m_Velocity=AddVertex3d(m_Velocity,ScaleVertex3d(Normalize3d(StaticModel::m_Dir),m_Speed));
                continue ;
            }
            if(Events[i].key.keysym.sym==SDLK_DOWN){
                m_Velocity=AddVertex3d(m_Velocity,ScaleVertex3d(Normalize3d(StaticModel::m_Dir),-m_Speed));
                continue ;
            }
            if(Events[i].key.keysym.sym==SDLK_RIGHT){
                m_Velocity=AddVertex3d(m_Velocity,ScaleVertex3d(Normalize3d(StaticModel::m_Right),m_Speed));
                continue ;
            }
            if(Events[i].key.keysym.sym==SDLK_LEFT){
                m_Velocity=AddVertex3d(m_Velocity,ScaleVertex3d(Normalize3d(StaticModel::m_Right),-m_Speed));
                continue ;
            }
            if(Events[i].key.keysym.sym==SDLK_x){
                Fire();
                continue ;
            }
        }
};
void HOPE::Fire(){
    v_Weapons[m_SelectedWeapon]->Fire(m_Scene,StaticModel::m_Pos,StaticModel::m_Dir,StaticModel::m_Up);
};
