#include "HOPE.h"
HOPE::HOPE():Player(){

};
HOPE::~HOPE(){

};
int HOPE::LoadFromFile() {
    m_Health=1000.0f;
    m_Charge=0 ;
    return StaticModel::LoadFromFile("model.obj");
};
void HOPE::Update(float dt){

};
void HOPE::Update(SDL_Event event){
    if()
};
void HOPE::SwitchWeapon(){

};
void HOPE::Fire(){

};
