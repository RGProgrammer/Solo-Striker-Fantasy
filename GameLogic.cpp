#include "GameLogic.h"

GameLogic::GameLogic():m_Scene(NULL),m_Camera(NULL),m_Player(NULL),m_EventSys(NULL),
                        m_Ship(NULL),m_MainMenu (NULL),m_ExitVariable(NULL),
                        m_CurrentLvlFilename(NULL),m_NextLvlFilename(NULL){
};
GameLogic::~GameLogic(){
    this->Destroy();
};
void GameLogic::Destroy(){
    m_Scene=NULL ;
    m_Camera=NULL ;
    m_Player=NULL ;
    if(m_Ship){
        m_Ship->Destroy();
        delete m_Ship;
        m_Ship=NULL ;
    }
    if(m_EventSys){
        delete m_EventSys ;
        m_EventSys=NULL ;
    }
};
int GameLogic::InitLogic(GameScene* Scene){
    this->m_Scene=Scene ;
    m_EventSys=new EventSystem();
    m_Ship=new HOPE();
    if(!m_Ship)
        return 0 ;
    if(!m_Ship->LoadFromFile())
        return 0 ;
    m_Camera=new Camera();
    m_Camera->setOrientation({0.0f,-1.0f,0.0f},{0.0f,0.0f,-1.0f});
    m_Camera->setPosition({0.0f,170.0f,0.0f});
    m_Scene->setCamera(m_Camera);
    m_Player=m_Ship;
    m_Ship->setScene(m_Scene);
    m_Scene->setPlayer(m_Player);
    return 1 ;
};
int GameLogic::InitLevel(char* filename){

    return 1 ;
};
void GameLogic::Update(float dt){
    Actor* actor=NULL ;
    unsigned int nbactors=m_Scene->getNBActors();
    //SDL_Event event=m_EventSys->getSDLEvent();
    SDL_Event* Events=m_EventSys->getCurrentFrameEvents() ;
    int nbEvents =m_EventSys->getNbEvents();
    if(Events[0].type==SDL_QUIT || Events[0].key.keysym.sym==SDLK_ESCAPE)
            *m_ExitVariable=false ;

    if(m_Player){
        m_Player->Update(Events,nbEvents);
        m_Player->Update(dt);
    }
    for(unsigned int i=0;i<nbactors;i++){
        actor=m_Scene->getActor(i);
        if(actor->getID() & UPDATABLE){
            dynamic_cast<Updatable*>(actor)->Update(dt);}
    }
};
 void GameLogic::setExitVariable(bool* variable){
    m_ExitVariable=variable ;
 };
