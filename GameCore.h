//////////////////////////////////////////////////////////////////////////////////
//                                  GameCore                                     //
//This is the Main/Core object of the game.this object creates, initialize and  //
//destroy all the game component                                                //
//                                                                              //
//////////////////////////////////////////////////////////////////////////////////
#ifndef PFE_GameCore_H_
#define PFE_GameCore_H_
#include "GameLogic.h"
#include "GraphicsEngine.h"
#include "GameScene.h"
#include "WindowHandler.h"
#include "Timer.h"
#include "Camera.h"
#include "Math.h"
#include ".//tools//sdl2//include//SDL.h"
#include <stdio.h>
class GameCore {
public :
    //Constructor
    GameCore () ;
    //Decinstructor
    ~GameCore();
    //Initializing object: must be called before calling StartGame methos
    int Init(char * Name,int Width, int Height,bool FullScreen=false, char* icon=NULL);
    //Game Loop
    void StartGame();
    //Free Resources
    void Destroy();
private :
    GameLogic*              m_Logic ;  //
    GraphicsEngine*         m_Graphics;//handles all graphical stuff
    GameScene*              m_Scene ;// this object is like a buffer.it contains all elements inside the Scene
    WindowHandler*          m_Window ;//Window
    Timer                   m_Timer ;// Timer
    bool                    m_Running ;// game Status: Running(true) or not(false)
};
#endif // PFE_GameCore_H_
