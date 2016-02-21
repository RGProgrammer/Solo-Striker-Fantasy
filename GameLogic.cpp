#include "GameLogic.h"

GameLogic::GameLogic():m_Scene(NULL),m_Camera(NULL),m_Player(NULL),m_EventSys(NULL),
                        m_Ship(NULL),m_MainMenu (NULL){
};
GameLogic::~GameLogic(){
    this->Destroy();
};
void GameLogic::Destroy(){
    m_Scene=NULL ;
    m_Camera=NULL ;
    if(m_Player){
        m_Player->Destroy();
        delete m_Player ;
        m_Player=NULL;
    }
    if(m_Ship){

    }
    if(m_EventSys){
        delete m_EventSys ;
        m_EventSys=NULL ;
    }
};
int GameLogic::InitLogic(GameScene* Scene){
    this->m_Scene=Scene ;
    //m_Player=new HOPE();
    //m_Player->LoadFromFile();
    return 1 ;
};
int GameLogic::InitLevel(char* filename){

    return 1 ;
};
void GameLogic::setCamera(Camera * camera){
    this->m_Camera=camera;
};
void GameLogic::Update(float dt){
    Actor* actor=NULL ;
    unsigned int nbactors=m_Scene->getNBActors();
    if(m_Player)
        m_Player->Update(dt);
    for(unsigned int i=0;i<nbactors;i++){
        actor=m_Scene->getActor(i);
        if(actor->getID() & UPDATABLE)
            ((Updatable*)actor)->Update(dt);
    }
};
Player* GameLogic::getPlayer(){
    return m_Player;
};
