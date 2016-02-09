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
    /*StaticModel* cube1=StaticModel::CreateCube();
    cube1->setPosition({0.0f,0.0f,-100.0f});
    m_Scene->AddActor((Actor**)(&cube1));
    StaticModel* cube2=StaticModel::CreateCube();
    cube2->setPosition({0.0f,0.0f,100.0f});
    m_Scene->AddActor((Actor**)(&cube2));
    StaticModel* cube3=StaticModel::CreateCube();
    cube3->setPosition({-100.0f,0.0f,0.0f});
    m_Scene->AddActor((Actor**)(&cube3));*/
    /*m_Player=new Player();
    if(m_Player){
        m_Scene->AddActor((Actor**)(&m_Player));
        m_Player->LoadFromFile(NULL);
    }*/
    return 1 ;

};
void GameLogic::setCamera(Camera * camera){
    this->m_Camera=camera;
};
void GameLogic::Update(float dt){
    Actor** actors=m_Scene->getActors();
    unsigned int nbactors=m_Scene->getNBActors();
    for(unsigned int i=0;i<nbactors;i++)
        if(actors[i]->getID() & UPDATABLE)
            ((Updatable*)(actors[i]))->Update(dt);
};
//Player* GameLogic::getPlayer(){
//    return m_Player;
//};
