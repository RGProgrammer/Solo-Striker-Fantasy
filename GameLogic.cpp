#include "GameLogic.h"

GameLogic::GameLogic():m_Scene(NULL),m_Camera(NULL)/*,m_Player(NULL)*/ {
};
GameLogic::~GameLogic(){
    this->Destroy();
};
void GameLogic::Destroy(){
    m_Scene=NULL ;
    m_Camera=NULL ;
    //m_Player->Destroy();
};
int GameLogic::InitLogic(GameScene* Scene){
    this->m_Scene=Scene ;
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
    for(unsigned int i=0;i<nbactors;i++){
        actor=m_Scene->getActor(i);
        if(actor->getID() & UPDATABLE)
            ((Updatable*)actor)->Update(dt);
    }
};
//Player* GameLogic::getPlayer(){
//    return m_Player;
//};
