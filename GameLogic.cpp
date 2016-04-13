#include "GameLogic.h"

GameLogic::GameLogic():m_Scene(NULL),m_Camera(NULL),m_Player(NULL),m_EventSys(NULL),
                        m_Ship(NULL),m_MainMenu (NULL),m_ExitVariable(NULL),
                        m_CurrentLevel(-1),v_Filenames(NULL),m_nbLevels(0),m_Physics(NULL),
                        m_SoundHandler(NULL),m_Delay(5.0f){
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
    if(m_Physics){
        delete m_Physics;
        m_Physics=NULL ;
    }
    if(m_SoundHandler){
        m_SoundHandler->Destroy();
        delete m_SoundHandler ;
        m_SoundHandler=NULL ;
    }
    if(v_Filenames){
        for(int i=0;i<m_nbLevels;i++)
            free(v_Filenames[i]);
        free(v_Filenames);
        v_Filenames=NULL ;
    }
};
int GameLogic::InitLogic(GameScene* Scene){
    this->m_Scene=Scene ;
    m_EventSys=new EventSystem();
    m_Physics=new PhysicsEngine(m_Scene);
    if(!m_Physics)
        return 0 ;
    m_Ship=new HOPE();
    if(!m_Ship)
        return 0 ;
    if(!m_Ship->LoadFromFile())
        return 0 ;
    m_MainMenu=new MainMenu() ;
    if(!m_MainMenu)
        return 0 ;
    if(!m_MainMenu->LoadFromFile())
        return 0 ;
    m_Camera=new Camera();
    m_Scene->setCamera(m_Camera);
    m_Player=m_MainMenu;
    m_Ship->setScene(m_Scene);
    m_MainMenu->setCamera(m_Camera);
    m_MainMenu->Init();
    m_Ship->setCamera(m_Camera);
    m_Scene->setPlayer(m_Player);
    m_Stat=MAINMENU ;
    m_nbLevels=1 ;
    v_Filenames=(char**)malloc(m_nbLevels*sizeof(char*));
    v_Filenames[0]=(char*)malloc(13*sizeof(char));
    strcpy(v_Filenames[0],"Desert.lvl");
    return 1 ;
};
int GameLogic::InitLevel(int index){
    /*UFO* e=NULL;
    Terrain* t=NULL;
    m_Scene->AddActor(StaticModel::LoadFile("Data//skybox.obj"));
    t=new Terrain();
    t->LoadFromFile("Data//Desert.obj");
    m_Scene->AddActor(t),
    e=new UFO();
    e->setPosition({0.0f,0.f,50.f});
    e->LoadFromFile();
    m_Scene->AddActor(e);
    e=new UFO();
    e->setPosition({20.0f,0.f,50.f});
    e->LoadFromFile();
    m_Scene->AddActor(e);
    e=new UFO();
    e->setPosition({-20.0f,0.f,50.f});
    e->LoadFromFile();
    m_Scene->AddActor(e);
    m_Camera->setOrientation({0.0f,-1.0f,0.0f},{0.0f,0.0f,-1.0f});
    m_Camera->setPosition({0.0f,150.0f,0.0f});
    */
    //m_Camera->setViewType(SIDE);
    if(!LevelLoader::LoadLevel(v_Filenames[index-1],m_Scene))
        return 0 ;
    return 1 ;
};
void GameLogic::Update(float dt){
    SDL_Event* Events=m_EventSys->getCurrentFrameEvents() ;
    int nbEvents =m_EventSys->getNbEvents();
    if(nbEvents>0 && Events[0].type==SDL_QUIT){
        *m_ExitVariable=false ;
        return ;
    }
    Actor* actor=NULL ;
    unsigned int nbactors=m_Scene->getNBActors();
    if(m_Stat==INGAME){
        if(Events[0].type==SDL_KEYDOWN){
            if(Events[0].key.keysym.sym==SDLK_ESCAPE){
                m_Scene->FreeVector();
                m_Player=m_MainMenu ;
                m_MainMenu->Init();
                m_Scene->setPlayer(m_Player);
                m_Stat=MAINMENU;
                return ;
            }
        }
        if(m_Player){
            m_Player->Update(Events,nbEvents);
            m_Player->Update(dt);
        }
        if(nbactors>0){
            for(unsigned int i=0;i<nbactors;i++){
                actor=m_Scene->getActor(i);
                if(actor->getID() & UPDATABLE){
                    dynamic_cast<Updatable*>(actor)->Update(dt);
                }else if(actor->getID() & UNKNOWN){
                    m_Scene->RemoveAt(i);
                }
            }
        }
        m_Physics->CollisioDetection();
        m_Physics->CollisionReaction();
        /*if(BossDefeated()){
            m_Delay-=dt;
            if(m_Delay<=0.0f)
                InitLevel(++m_CurrentLevel);
        }*/
    }else if(m_Stat==MAINMENU){

            if(Events[0].type==SDL_QUIT || Events[0].key.keysym.sym==SDLK_ESCAPE)
                *m_ExitVariable=false ;
        if(Events[0].type==SDL_KEYDOWN){
            if(Events[0].key.keysym.sym==SDLK_z){
                if(m_MainMenu->getSelectedItem()==STARTGAME){
                    m_Player=m_Ship ;
                    m_Scene->setPlayer(m_Player);
                    this->InitLevel(1);
                    m_Stat=INGAME ;
                    return ;
                }else if(m_MainMenu->getSelectedItem()==EXIT)
                    *m_ExitVariable=false;
            }
        }
        if(m_Player){
            m_Player->Update(Events,nbEvents);
            m_Player->Update(dt);
        }
    }else if(m_Stat==PAUSE){
        if(Events[0].key.keysym.sym==SDLK_s){
            m_Stat==INGAME ;
        }

    }
};
 void GameLogic::setExitVariable(bool* variable){
    m_ExitVariable=variable ;
 };
