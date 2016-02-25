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
//#include "Cube.h"
//#include "UFO.h"
#include ".//tools//sdl2//include//SDL.h"


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
    int InitLevel(char* filename);
    void Update(float dt);
    void setExitVariable(bool* variable);
private:
    GameScene*          m_Scene ;
    Camera*             m_Camera ;
    int                 m_Stat ;
    HOPE*               m_Ship;
    MainMenu*           m_MainMenu ;
    Player*             m_Player ;
    EventSystem*        m_EventSys ;
    char*               m_CurrentLvlFilename ;
    char*               m_NextLvlFilename ;
    bool*               m_ExitVariable ;

};
#endif // PFE_GAMELOGIC_H_
