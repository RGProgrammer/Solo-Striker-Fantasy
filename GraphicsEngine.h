/////////////////////////////////////////////////////////////////////////////////
//                          GraphicsEngine                                     //
//it work is simple:each time the main program call the DrawScene() method     //
//it gets a reference of the Scene Camera(for view transformation) and search  //
//for all Drawable object in the GameScene to call their Draw function         //
//                                                                             //
/////////////////////////////////////////////////////////////////////////////////
#ifndef PFE_GRAPHICSENGINE_H_
#define PFE_GRAPHICSENGINE_H_
#include "Abstract.h"
#include "GameScene.h"
#include "WindowHandler.h"
#include ".//tools//sdl2//include//SDL.h"
#include ".//tools//sdl2//include//SDL_opengl.h"
#include <GL//glu.h>

class GraphicsEngine {
public :
    GraphicsEngine();
    ~GraphicsEngine();
    int InitEngine(WindowHandler* Window, GameScene* Scene );
    void Destroy() ;
    void DrawScene();
    void setScene(GameScene* Scene);
private:
    GameScene*                  m_Scene;
    WindowHandler*              m_Hwnd ;
};
#endif // PFE_GRAPHICSENGINE_H_
