#ifndef PFE_PLAYER_H_
#define PFE_PLAYER_H_
#include "DynamicModel.h"
#include "GameScene.h"
#include ".//tools//sdl2//include//SDL.h"
#define NOTHING 0x0000
#define HIT     0x0001
#define FIRE    0x0002

class Player:public DynamicModel{
public:
    Player();
    Player(Vertex3d Pos);
    Player(Vertex3d Pos,Vertex3d Dir,Vertex3d Up);
    ~Player();
    int LoadFromFile();
    void setScene(GameScene* Scene);
    void Update(float dt);
    void Update(SDL_Event event);
private:
    int                 m_State;
    GameScene*          m_Scene;
};
#endif // PFE_PLAYER
