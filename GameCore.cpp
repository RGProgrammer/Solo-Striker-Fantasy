#include "GameCore.h"
GameCore::GameCore ():m_Logic(NULL), m_Graphics(NULL), m_Scene(NULL), m_Window(NULL),
                    m_Running(false)
{};
GameCore::~GameCore(){
    this->Destroy();
};
int GameCore::Init(char * Name,int Width, int Height,bool FullScreen, char* icon){
    if(SDL_Init(SDL_INIT_EVERYTHING)!=0){
        return 0 ;
    }
    //create and Initilize the Window object
    m_Window=new WindowHandler();
    if(!m_Window)
        return 0 ;
    if(!m_Window->InitWindow(Name,Width,Height,FullScreen,icon))
        return 0 ;
    //Create and Init the GameScene
    m_Scene=new GameScene();
    if(!m_Scene)
        return 0 ;
    //Create and Init the Graphics engine
    m_Graphics=new GraphicsEngine();
    if(!m_Graphics)
        return 0 ;
    if(!m_Graphics->InitEngine(m_Window,m_Scene))
        return 0 ;
    //Create and Init the Game Logic
    m_Logic=new GameLogic();
    if(!m_Logic)
        return 0 ;
    if(!m_Logic->InitLogic(m_Scene))
        return 0 ;
        m_Camera=new Camera();
    return 1 ;
};
void GameCore::StartGame(){
    m_Running=true ;
    SDL_Event event ;
    m_Timer.Reset();
    if(!m_Logic->InitLevel(NULL))
        return ;
//    Player* player=m_Logic->getPlayer();
    m_Camera->setPosition({0.0f,300.0f,0.0f});
    m_Camera->setOrientaion({0.0f,-1.0f,0.0f},{0.0f,0.0f,-1.0f});
    m_Scene->setCamera(m_Camera);
    while(m_Running){
        SDL_PollEvent(&event);
        if(event.type==SDL_QUIT || event.key.keysym.sym==SDLK_ESCAPE){
            m_Running=false ;
            continue ;
        }
        //if(player)
        //    player->Update(event);
        m_Logic->Update(0.0f);
        m_Graphics->DrawScene();
    }
};
void GameCore::Destroy(){
    if(m_Logic){
        m_Logic->Destroy();
        delete m_Logic ;
        m_Logic=NULL ;
    };
    if(m_Graphics){
        m_Graphics->Destroy();
        delete m_Graphics ;
        m_Graphics=NULL ;
    }
    if(m_Scene){
        m_Scene->Destroy();
        delete m_Scene ;
        m_Scene=NULL ;
    }
    if(m_Window){
        m_Window->Destroy();
        delete m_Window ;
        m_Window=NULL ;
    }
    SDL_Quit();
    //m_Timer.Stop();
};
