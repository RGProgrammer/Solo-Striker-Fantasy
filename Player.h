#ifndef PFE_PLAYER_H_
#define PFE_PLAYER_H_
#include "DynamicModel.h"
#include "GameScene.h"
#include ".//tools//sdl2//include//SDL.h"
#define DEAD        0x0000
#define MOVING      0x0001
#define HIT         0x0002
#define FIRE        0x0004
#define CHARGING    0x0008
#define NOTHING     0x0010


class Player:public DynamicModel{
public:
    Player();
    Player(Vertex3d Pos);
    Player(Vertex3d Pos,Vertex3d Dir,Vertex3d Up);
    virtual ~Player();
    void setScene(GameScene* Scene);
    virtual int LoadFromFile()=0;
    virtual void Update(float dt)=0;
    virtual void Update(SDL_Event event)=0;
protected:
    GameScene*          m_Scene;
    Weapon*             m_SelectedWeapon;
    Weapon**            v_Weapons
    int                 m_Health;
    int                 m_Charge;
    int                 m_nbWeapons
    int                 m_State;
    Vertex3d            m_MoveDirection;

};
#endif // PFE_PLAYER
