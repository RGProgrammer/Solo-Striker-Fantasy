#include "MainMenu.h"

MainMenu::MainMenu():Player(),v_SubItems(NULL) ,m_nbItems(0),m_Selected(0){
};
MainMenu::~MainMenu(){
    Destroy();
};
int MainMenu::LoadFromFile(){
/*
    if(!this->LoadFromFile("Data//BackGround.obj"))
        return 0 ;
    m_nbItems=3 ;
    m_Selected=0 ;
    v_SubItems=(StaticModel**)calloc(3*sizeof(void*));
    if(!v_SubItems)
        return 0 ;
    v_SubItems[0]=StaticModel::LoadFile("Data//Start.obj") ;
    //v_SubItems[0]->setPosition({,,});
    v_SubItems[1]=StaticModel::LoadFile("Data//Score.obj") ;
    //v_SubItems[1]->setPosition({,,});
    v_SubItems[2]= StaticModel::LoadFile("Data//Exit.obj") ;
    //v_SubItems[2]->setPosition({,,});
    m_Selector=LoadFile("Data//Selector.obj");
    m_Selector->setPosition(v_SubItems[m_Selected]->getPosition());*/
    return 1 ;
};
void MainMenu::Update(float dt){

};
void MainMenu::Update(SDL_Event* Events, int nbEvents){
   if(m_nbItems>0)
    for(int i=0 ;i<nbEvents ;i++){
        if(Events[i].type==SDL_KEYDOWN){
            if(Events[i].key.keysym.sym==SDLK_UP){
                m_Selected--;
                if(m_Selected<0)
                    m_Selected=m_nbItems-1 ;
            }else if(Events[i].key.keysym.sym==SDLK_DOWN){
                m_Selected++;
                if(m_Selected=m_nbItems)
                    m_Selected=0 ; ;
            }
            m_Selector->setPosition(v_SubItems[m_Selected]->getPosition());
        }
    }
};
int MainMenu::getSelectedItem(){
    return m_Selected ;
};
 void MainMenu::Draw(float* viewMtx){
    StaticModel::Draw(viewMtx);
    for(int i= 0 ; i< m_nbItems ;i++)
        v_SubItems[i]->Draw(viewMtx);
};
void MainMenu::Destroy(){
    Player::Destroy();
    if(v_SubItems){
        for(int i=0;i<m_nbItems;i++)
            v_SubItems[i]->Destroy();
        free(v_SubItems);
        m_nbItems=0;
        m_Selected=-1;
    }
};
