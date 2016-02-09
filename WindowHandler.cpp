#include "WindowHandler.h"
WindowHandler::WindowHandler():m_Hwnd(NULL) ,m_Height(0),m_Width(0),m_FullScreen(false){};
WindowHandler::~WindowHandler(){
    this->Destroy() ;
};
int WindowHandler::InitWindow(char * Title,int Width,int Height,
                                    bool FullScreen,char* Icon){
    if(!FullScreen)
        m_Hwnd=SDL_CreateWindow(Title,SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,Width,Height,
                               SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
    else
        m_Hwnd=SDL_CreateWindow(Title,SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,Width,Height,
                               SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN |SDL_WINDOW_FULLSCREEN );
    if(!m_Hwnd)
        return 0;
    m_Height=Height;
    m_Width=Width ;
    m_FullScreen=FullScreen ;
    return 1;

};
void WindowHandler::Destroy(){

    SDL_DestroyWindow(m_Hwnd);
    m_Hwnd=NULL;
    m_Height=m_Width=0;
    m_FullScreen=false ;
};
SDL_Window* WindowHandler::getSDLWin(){return m_Hwnd;};
int WindowHandler::Resize(int Width,int Height){
    SDL_SetWindowSize(m_Hwnd,Width,Height);
    m_Height=Height;
    m_Width=Width;
    return 1;
};
int WindowHandler::SetFullScreen(bool Res){
    if(Res && !m_FullScreen)
        SDL_SetWindowFullscreen(m_Hwnd,SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN |SDL_WINDOW_FULLSCREEN);
    else if(!Res && m_FullScreen)
        SDL_SetWindowFullscreen(m_Hwnd,SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
    return 1;
};
int WindowHandler::getHeight(){return m_Height;};
int WindowHandler::getWidth() {return m_Width;};
