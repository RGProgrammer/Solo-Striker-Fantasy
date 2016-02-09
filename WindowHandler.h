//////////////////////////////////////////////////////////////////////////////////////
//                        WindowHandler                                             //
//this object handle the Window on any operating system that is supported by SDL2   //
//since SDL2 is Cross Platform library and all the neccessarly opeartions(methods)  //
//needed for this project                                                           //
//                                                                                  //
//////////////////////////////////////////////////////////////////////////////////////
#ifndef PFE_WINDOWHANDLER_H_
#define PFE_WINDOWHANDLER_H_
#include ".//tools//sdl2//include//SDL.h"
class WindowHandler {
public:
    //Constructor
    WindowHandler();
    //Deconstructor
    ~WindowHandler();
    //create a window: 1 created with success ,0 failed
    int InitWindow(char * Title,int Width,int Height,bool FullScreen=false,char* Icon=NULL);
    //release all resourcs used by this object
    void Destroy();
    //return a pointer a the window main surface
    SDL_Window* getSDLWin();
    //resize the window: 1 success , 0 failed
    int Resize(int Widh,int Height);
    // switch between fullscreen and windowed mode
    int SetFullScreen(bool Res);
    //getters
    int getHeight();
    int getWidth() ;
private :
    SDL_Window*         m_Hwnd ;
    int                 m_Height,m_Width;
    bool                m_FullScreen ;
};
#endif // PFE_WINDOWHANDLER_H_
