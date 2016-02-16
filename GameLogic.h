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
//#include "Player.h"
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
    void setCamera(Camera * camera);
    void Update(float dt);
//    Player* getPlayer();
private:
    GameScene*          m_Scene ;
    Camera*             m_Camera ;
    int                 m_Stat ;
    //SDL_Event           event;
    //Player*           m_Player ;
    //EventManager*     m_EventSys ;
};
#endif // PFE_GAMELOGIC_H_
