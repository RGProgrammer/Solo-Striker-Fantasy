#ifndef PFE_PLAYER_H_
#define PFE_PLAYER_H_
#include "GameScene.h"
#include "DynamicModel.h"
#include "Weapon.h"
#include ".//tools//sdl2//include//SDL.h"
#define DEAD        0x0000
#define MOVING      0x0001
#define HIT         0x0002
#define FIRE        0x0004
#define CHARGING    0x0008
#define NOTHING     0x0010

class GameScene ;
class Weapon ;
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
    void NextWeapon();
    void PreviousWeapon();
protected:
    Vertex3d            m_MoveDirection;
    int                 m_Health;
    int                 m_Charge;
    int                 m_nbWeapons;
    int                 m_State;
    int                 m_SelectedWeapon;
    GameScene*          m_Scene;
    Weapon**            v_Weapons;

};
#endif // PFE_PLAYER
