#ifndef PFE_WEAPON_H_
#define PFE_WEAPON_H_
#include "Shot.h"
#include "GameScene.h"
class GameScene ;
class Weapon{
public:
    Weapon(char* Name);
    Weapon(char* Name,Actor* Owner);
    Weapon(char* Name,Actor* Owner,Shot* Sample);
    void setSample(Shot* Sample);
    virtual int Fire(GameScene* Scene,Vertex3d Pos,Vertex3d Dir,Vertex3d Up)=0;
    char* getName();
protected:
    char*           m_Name ;
    Shot*           m_Sample;
    float           m_TimeBetweenShots;
    Actor*          m_Owner;
    float           m_Dt ;
};
#endif // PFE_WEAPON_H_
