#include "MainMenu.h"

MainMenu::MainMenu():Player(),v_SubItems(NULL) ,m_nbItems(0),m_Selected(0){
};
MainMenu::~MainMenu(){
    Player::Destroy();
    if(v_SubItems){
        for(int i=0;i<m_nbItems;i++)
            v_SubItems[i]->Destroy();
        free(v_SubItems);
        m_nbItems=0;
        m_Selected=-1;
    }
};
int MainMenu::LoadFromFile(){
    return 1 ;
};
void MainMenu::Update(float dt){

};
void MainMenu::Update(SDL_Event* Events, int nbEvents){

};
int MainMenu::getSelectedItem(){
    return m_Selected ;
};
 void MainMenu::Draw(float* viewMtx){
    StaticModel::Draw(viewMtx);
    //Draw the menu item
};
