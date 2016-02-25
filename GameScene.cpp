#include "GameScene.h"
GameScene::GameScene():Size(10),m_NBActors(0),v_Actors(NULL),m_Camera(NULL){};
GameScene::~GameScene() {
    this->Destroy() ;
};
int GameScene::AddActor(Actor* actor){
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
    if(v_Actors){
        for(unsigned int i=0;i<m_NBActors ;i++)
            v_Actors[i]->Destroy();
        free(v_Actors);
        v_Actors=NULL ;
        m_NBActors=0 ;
        Size=10;
    }
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
};
void GameScene::setCamera(Camera* Cam){
    this->m_Camera=Cam;
};
Camera* GameScene::getCamera(){
    return m_Camera ;
};
void GameScene::RemoveAt(unsigned int index){
    if(index==m_NBActors-1){
        v_Actors[index]->Destroy();
        delete (v_Actors[index]) ;
        }
    else if(index>=0 && index< m_NBActors-1){
         v_Actors[index]->Destroy();
        delete (v_Actors[index]) ;
        for(unsigned int i=index;i<m_NBActors-1;i++)
            v_Actors[i]=v_Actors[i+1];
    }
    m_NBActors-- ;
};
