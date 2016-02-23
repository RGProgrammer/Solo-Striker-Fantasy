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
    m_Speed=1.0f;
    return StaticModel::LoadFromFile("Data//Model.obj");
};
void HOPE::Update(float dt){
    StaticModel::m_Pos=AddVertex3d(StaticModel::m_Pos,ScaleVertex3d(m_Velocity,1.0f));
    m_Velocity={0.0f,0.0f,0.0f};
};
void HOPE::Update(SDL_Event event){
    if(event.type==SDL_KEYDOWN){
        if(event.key.keysym.sym==SDLK_UP){
                m_Velocity=AddVertex3d(m_Velocity,ScaleVertex3d(Normalize3d(StaticModel::m_Dir),m_Speed));
        }
        else if(event.key.keysym.sym==SDLK_DOWN){
                m_Velocity=AddVertex3d(m_Velocity,ScaleVertex3d(Normalize3d(StaticModel::m_Dir),-m_Speed));
        }
        else if(event.key.keysym.sym==SDLK_RIGHT){
                m_Velocity=AddVertex3d(m_Velocity,ScaleVertex3d(Normalize3d(StaticModel::m_Right),m_Speed));
        }
        else if(event.key.keysym.sym==SDLK_LEFT){
                m_Velocity=AddVertex3d(m_Velocity,ScaleVertex3d(Normalize3d(StaticModel::m_Right),-m_Speed));
        }
        else if(event.key.keysym.sym==SDLK_x){
                Fire();

        }else if(event.key.keysym.sym==SDLK_r){
            StaticModel::setPosition({0.0f,0.0f,0.0f});
        }

    }
};
void HOPE::Fire(){
    v_Weapons[m_SelectedWeapon]->Fire(m_Scene,StaticModel::m_Pos,StaticModel::m_Dir,StaticModel::m_Up);
};
