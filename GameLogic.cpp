#include "GameLogic.h"

GameLogic::GameLogic():m_Scene(NULL),m_Camera(NULL),m_Player(NULL),m_EventSys(NULL),
                        m_Ship(NULL),m_MainMenu (NULL),m_ExitVariable(NULL),
                        m_CurrentLevel(-1),v_Filenames(NULL),m_nbLevels(0),m_Physics(NULL),
                        m_Delay(5.0f),m_ScoreDisplay(NULL),v_Scores(NULL){
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
    if(v_Filenames){
        for(int i=0;i<m_nbLevels;i++)
            free(v_Filenames[i]);
        free(v_Filenames);
        v_Filenames=NULL ;
    }
    if(m_ScoreDisplay){
        m_ScoreDisplay->Destroy();
        delete m_ScoreDisplay;
        m_ScoreDisplay=NULL ;
    }
    if(v_Scores){
        free(v_Scores);
        v_Scores=NULL ;
    }
    DestroyGlobalSoundEngine();
};
int GameLogic::InitLogic(GameScene* Scene){
    this->m_Scene=Scene ;
    m_EventSys=new EventSystem();
    m_Physics=new PhysicsEngine(m_Scene);
    if(!CreateGlobalSoundEngine()){
        //printf("Cannot create Soound engine\n");
        return 0 ;
    }
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
    m_Ship->setCamera(m_Camera);
    m_Scene->setPlayer(m_Player);
    m_Stat=MAINMENU ;
    m_nbLevels=1 ;
    v_Filenames=(char**)malloc(m_nbLevels*sizeof(char*));
    v_Filenames[0]=(char*)malloc(13*sizeof(char));
    strcpy(v_Filenames[0],"Desert.lvl");
    m_MainMenu->Init();
    m_ScoreDisplay=new ScoreDisplay();
    m_ScoreDisplay->LoadFromFile();
    m_ScoreDisplay->setPosition({0.0f,0.0f,-10.0f});
    v_Scores=(unsigned int*)malloc(5*sizeof(unsigned int));
    for(int i =0 ;i<5; i++)
        v_Scores[i]=0 ;
    return 1 ;
};
int GameLogic::InitLevel(int index){
    if(!LevelLoader::LoadLevel(v_Filenames[index-1],m_Scene))
        return 0 ;
    getGlobalSoundEngineInstance()->PlayMusic();
    m_Delay=5.0f ;
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
        if(nbEvents)
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
        if(m_Player->getStat()!=CHECK){
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
            m_Physics->CollisioDetection(dt);
            m_Physics->CollisionReaction();
        }
        if(!isThereEnemy()){
            m_Delay-=dt;
            if(m_Delay<=0.0f)
                if(m_CurrentLevel<m_nbLevels){
                    v_Scores[m_CurrentLevel-1]=m_Player->getScore();
                    InitLevel(++m_CurrentLevel);
                }else{
                    v_Scores[m_CurrentLevel-1]=m_Player->getScore();
                    SwitchtoSCORESCREEN();
                    return ;
                }
        }
    }else if(m_Stat==MAINMENU){
        if(nbEvents){
        if(Events[0].type==SDL_QUIT || Events[0].key.keysym.sym==SDLK_ESCAPE)
                *m_ExitVariable=false ;
        if(Events[0].type==SDL_KEYDOWN){
            if(Events[0].key.keysym.sym==SDLK_z){
                if(m_MainMenu->getSelectedItem()==STARTGAME){
                    SwitchtoINGAME();
                    return ;
                }else if(m_MainMenu->getSelectedItem()==EXIT){
                    *m_ExitVariable=false;
                    return ;
                }else if(m_MainMenu->getSelectedItem()==SCORE){
                    SwitchtoSCORESCREEN();
                    m_Stat=SCORESCREEN;
                    return ;
                }
            }
        }
        }
        if(m_Player){
            m_Player->Update(Events,nbEvents);
            m_Player->Update(dt);
        }
    }else if(m_Stat==PAUSE){
        if(nbEvents)
        if(Events[0].type==SDL_KEYDOWN)
            if(Events[0].key.keysym.sym==SDLK_s){
                m_Stat==INGAME ;
                return ;
            }
    }else if(m_Stat==SCORESCREEN){
        if(nbEvents)
        if(Events[0].type==SDL_KEYDOWN)
            if(Events[0].key.keysym.sym==SDLK_z){
                SwitchtoMAINMENU();
                return ;
            }
    }
};
 void GameLogic::setExitVariable(bool* variable){
    m_ExitVariable=variable ;
 };
 bool GameLogic::isThereEnemy(){
    unsigned int nbActors=m_Scene->getNBActors();
    for(unsigned int i=0 ; i< nbActors;i++)
        if(m_Scene->getActor(i)->getID()& ENEMY)
            return true ;
    return false ;
 };
void GameLogic::SwitchtoMAINMENU(){
    m_Scene->FreeVector();
    m_ScoreDisplay=NULL ;
    m_Player=m_MainMenu ;
    m_MainMenu->Init();
    m_Scene->setPlayer(m_Player);
    m_Stat=MAINMENU;
};
void GameLogic::SwitchtoINGAME(){
    m_Player=m_Ship ;
    m_Scene->setPlayer(m_Player);
    m_Ship->Init();
    InitLevel(m_CurrentLevel=1);
    m_Stat=INGAME ;
};
void GameLogic::SwitchtoSCORESCREEN(){
    m_Scene->FreeVector();
    m_Player=NULL;
    m_Scene->setPlayer(m_Player);
    m_ScoreDisplay=new ScoreDisplay();
    m_ScoreDisplay->LoadFromFile();
    m_ScoreDisplay->setPosition({0.0f,0.0f,-4.5f});
    m_ScoreDisplay->GenerateDisplay(v_Scores);
    m_Scene->AddActor(m_ScoreDisplay);
    m_Stat=SCORESCREEN ;
};
