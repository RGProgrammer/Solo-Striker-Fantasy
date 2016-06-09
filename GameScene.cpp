#include "GameScene.h"
GameScene::GameScene():Size(10),m_NBActors(0),v_Actors(NULL),m_Camera(NULL),
                        m_MinVertex({-85.0f,-65.0f,-85.0f}),m_MaxVertex({85.0f,65.0f,85.0f}){};
GameScene::~GameScene() {
    this->Destroy() ;
};
int GameScene::AddActor(Actor* actor){
    if(actor==NULL)
        return 0 ;
    if(v_Actors==NULL){
        v_Actors=(Actor**)malloc((Size)*sizeof(Actor*));
        if(v_Actors==NULL)
            return 0 ;
    }
    if(m_NBActors==Size){
        Actor** tmp=v_Actors ;
        // allocation of bigger vetor
        v_Actors=(Actor**)malloc((Size+10)*sizeof(Actor*));
        if(v_Actors==NULL){
            v_Actors=tmp;
            return 0;
        }
        //coping old vector data
        Size+=10 ;
        for(unsigned int i=0 ; i<m_NBActors;i++)
            v_Actors[i]=tmp[i];
        free(tmp);
        }
        v_Actors[m_NBActors]=actor ;
        m_NBActors++;
        return 1 ;
};
void GameScene::FreeVector(){
    Actor* tmp=NULL ;
    if(v_Actors){
        for(unsigned int i=0;i<m_NBActors ;i++){
            tmp=v_Actors[i];
            tmp->Destroy();
            delete tmp;
        }
        free(v_Actors);
    }
    v_Actors=NULL ;
    m_NBActors=0 ;
    Size=10;
};
Actor*  GameScene::getActor(unsigned int index){
    if(index>=m_NBActors)
        return NULL ;
    return v_Actors[index];
};
int GameScene::getNBActors(){ return m_NBActors ;};
void GameScene::setPlayer(Player * player){
    m_Player=player;
};
Player* GameScene::getPlayer(){
    return m_Player ;
};
void GameScene::Destroy() {
    this->FreeVector();
    m_Player=NULL ;
    m_Camera=NULL;
};
void GameScene::setCamera(Camera* Cam){
    this->m_Camera=Cam;
};
Camera* GameScene::getCamera(){
    return m_Camera ;
};
void GameScene::RemoveAt(unsigned int index){
    Actor* tmp =NULL ;
    if(index>=0 && index< m_NBActors){
        tmp=v_Actors[index] ;
        tmp->Destroy();
        delete tmp ;
        for(unsigned int i=index;i<m_NBActors-1;i++)
            v_Actors[i]=v_Actors[i+1];
        m_NBActors-- ;
    }
};
void GameScene::setBorders(Vertex3d MinVertex, Vertex3d MaxVertex){
    m_MinVertex=MinVertex ;
    m_MaxVertex=MaxVertex ;
};
void GameScene::getBorders(Vertex3d* MinVertex,Vertex3d* MaxVertex){
    if(MinVertex)
        *MinVertex=m_MinVertex ;
    if(MaxVertex)
        *MaxVertex=m_MaxVertex ;
};
