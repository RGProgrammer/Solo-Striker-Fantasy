//////////////////////////////////////////////////////////////////////////////////
//                      GameLogic                                               //
//how the game should behave is defined in this Classe.it handles the creation  //
//and initilazation of levels and its objects and all updatable object in       //
//the gamescene                                                                 //
//                                                                              //
//////////////////////////////////////////////////////////////////////////////////

#ifndef PFE_GAMELOGIC_H_
#define PFE_GAMELOGIC_H_
#include "GameScene.h"
#include "Abstract.h"
#include "Camera.h"
#include "HOPE.h"
#include "MainMenu.h"
#include "EventSystem.h"
#include "PhysicsEngine.h"
#include "SoundEngine.h"
#include "LevelLoader.h"
#include ".//tools//sdl2//include//SDL.h"

//nomber of level
#define NBLEVELS            5
//Game Logic Stats
#define     MAINMENU        0x0001
#define     INGAME          0x0002
#define     PAUSE           0x0004
#define     SCORESCREEN     0x0008

class GameLogic {
public:
    GameLogic();
    ~GameLogic() ;
    void Destroy();
    int InitLogic(GameScene* Scene);
    int InitLevel(int index);
    void Update(float dt);
    void setExitVariable(bool* variable);
private:
    bool isThereEnemy();
    int                 m_Stat ;
    float               m_Delay ;
    char**              v_Filenames;
    int                 m_nbLevels;
    int                 m_CurrentLevel ;
    bool*               m_ExitVariable ;
    GameScene*          m_Scene ;
    Camera*             m_Camera ;
    HOPE*               m_Ship;
    MainMenu*           m_MainMenu ;
    Player*             m_Player ;
    EventSystem*        m_EventSys ;
    PhysicsEngine*      m_Physics ;
    SoundEngine*        m_SoundHandler ;


};
#endif // PFE_GAMELOGIC_H_
