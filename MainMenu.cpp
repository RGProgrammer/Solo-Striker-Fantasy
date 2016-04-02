#include "MainMenu.h"

MainMenu::MainMenu():Player(),v_SubItems(NULL) ,m_nbItems(0),m_Selected(0){
};
MainMenu::~MainMenu(){
    Destroy();
};
int MainMenu::LoadFromFile(){
    if(!StaticModel::LoadFromFile("Data//BackGround.obj"))
        return 0 ;
    m_nbItems=3 ;
    m_Selected=0 ;
    v_SubItems=(StaticModel**)malloc(3*sizeof(StaticModel*));
    if(!v_SubItems)
        return 0 ;
    v_SubItems[0]=StaticModel::LoadFile("Data//start.obj") ;
    v_SubItems[0]->setPosition({0.0f,-1.0f,2.0f});
    v_SubItems[1]=StaticModel::LoadFile("Data//score.obj") ;
    v_SubItems[1]->setPosition({0.0f,-1.0f,0.0f});
    v_SubItems[2]= StaticModel::LoadFile("Data//exit.obj") ;
    v_SubItems[2]->setPosition({0.0f,-1.0f,-2.0f});
    m_Selector=LoadFile("Data//Selector.obj");
    Vertex3d pos=v_SubItems[m_Selected]->getPosition();
    pos.y+=0.5f;
    m_Selector->setPosition(pos);
    return 1 ;
};
void MainMenu:: Init(){
     m_Selected=0 ;
     if(m_Camera){
        m_Camera->setOrientation({0.0f,-1.0f,0.0f},{0.0f,0.0f,-1.0f});
        m_Camera->setPosition({0.0f,39.0f,0.0f});
     }
}
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
                if(m_Selected==m_nbItems)
                    m_Selected=0 ; ;
            }
            Vertex3d pos=v_SubItems[m_Selected]->getPosition();
            pos.y+=0.5f;
            m_Selector->setPosition(pos);

        }
    }
};
int MainMenu::getSelectedItem(){
    return m_Selected ;
};
 void MainMenu::Draw(float* viewMtx){
    StaticModel::Draw(viewMtx);
    m_Selector->Draw(viewMtx);
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
