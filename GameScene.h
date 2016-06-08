/////////////////////////////////////////////////////////////////////////////////////
//                          GameScene                                              //
//the GameScene could be considered as a handler of the Game-objects'reference     //
//all the game Objects that could be placed in the scene are 'Actor' based Objects //
//                                                                                 //
/////////////////////////////////////////////////////////////////////////////////////
#ifndef PFE_GAMESCENE_H_
#define PFE_GAMESCENE_H_
#include "StaticModel.h"
#include "Camera.h"
#include "Player.h"
class Player ;
class GameScene {
public:
    GameScene();
    ~GameScene() ;
    int AddActor(Actor* actor);
    void FreeVector();
    void Destroy() ;
    Actor*  getActor(unsigned int index);
    int getNBActors();
    void setPlayer(Player * player);
    Player* getPlayer();
    void setCamera(Camera*);
    Camera* getCamera();
    void RemoveAt(unsigned int index);
    void setBorders(Vertex3d MinVertex, Vertex3d MaxVertex);
    void getBorders(Vertex3d* MinVertex,Vertex3d* MaxVertex);
private:
    unsigned int        Size ;
    unsigned int        m_NBActors ;
    Actor**             v_Actors ;
    Player*             m_Player ;
    Camera*             m_Camera ;
    Vertex3d            m_MinVertex ;
    Vertex3d            m_MaxVertex ;
};
#endif // PFE_GAMESCENE_H_
