#ifndef PFE_PLAYER_H_
#define PFE_PLAYER_H_
#include "GameScene.h"
#include "DynamicModel.h"
#include "Weapon.h"
#include "ScoreHandler.h"
#include ".//tools//sdl2//include//SDL.h"
//Actor ID
#define PLAYER      0x0040

//Player Stats
#define DEAD        0x0000
#define ALIVE       0x0001
#define HIT         0x0004
#define CHECK       0x0008
#define FIRE        0x0010
#define CHARGING    0x0020

class GameScene ;
class Weapon ;
class Player:public DynamicModel{
public:
    Player();
    Player(Vertex3d Pos);
    Player(Vertex3d Pos,Vertex3d Dir,Vertex3d Up);
    virtual ~Player();
    void setScene(GameScene* Scene);
    void setCamera(Camera* Cam);
    virtual int LoadFromFile()=0;
    virtual void Update(float dt)=0;
    virtual void Update(SDL_Event* Events, int nbEvents)=0 ;
    virtual void getDamage() ;
    void setScore(unsigned int Score);
    unsigned int getScore();
    void AddtoScore(unsigned int Value);
    int getStat();
protected:
    int                 m_Stat ;
    int                 m_Charge;
    GameScene*          m_Scene;
    Camera*             m_Camera;
    ScoreHandler*       m_Score ;


};
#endif // PFE_PLAYER
