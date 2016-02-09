#include "GraphicsEngine.h"
GraphicsEngine::GraphicsEngine():m_Scene(NULL),m_Hwnd(NULL) {
};
GraphicsEngine::~GraphicsEngine(){
    this->Destroy();
};
int GraphicsEngine::InitEngine(WindowHandler* Window, GameScene* Scene ){
    m_Hwnd=Window ;
    m_Scene=Scene ;
    SDL_GLContext context=SDL_GL_CreateContext(m_Hwnd->getSDLWin());
    if(context==NULL)
        return 0 ;
    glViewport(0,0,m_Hwnd->getWidth(),m_Hwnd->getHeight());
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glDisable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f,(float)m_Hwnd->getWidth()/(float)m_Hwnd->getHeight(),1.0f,1000.0f);
    return 1 ;
};
void GraphicsEngine::Destroy() {
    m_Hwnd=NULL ;
    m_Scene=NULL ;
};
void GraphicsEngine::DrawScene(){
    Camera* m_Camera=m_Scene->getCamera();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.5f,0.5f,0.5f,0.0f);
    if(m_Scene){
        Actor** actors = m_Scene->getActors();
        unsigned int nbActors=m_Scene->getNBActors();
        for(unsigned int i=0;i<nbActors;i++)
            if(actors[i]->getID() & DRAWABLE){
                if(m_Camera)
                    ((Drawable*)(actors[i]))->Draw(m_Camera->getTransMtx());
                else
                    ((Drawable*)(actors[i]))->Draw(NULL);
            }
    }
    SDL_GL_SwapWindow(m_Hwnd->getSDLWin());
};
void GraphicsEngine::setScene(GameScene* Scene){
    m_Scene=Scene ;
};
