#ifndef PFE_WEAPON_H_
#define PFE_WEAPON_H_
#include "GlobalSound.h"
#include "Shot.h"
#include "GameScene.h"
class GameScene ;
class Weapon{
public:
    Weapon(char* Name);
    Weapon(char* Name,Actor* Owner);
    Weapon(char* Name,Actor* Owner,Shot* Sample);
    void setSample(Shot* Sample);
    void setOwner(Actor* Owner);
    virtual int Fire(GameScene* Scene,Vertex3d Pos,Vertex3d Dir,Vertex3d Up)=0;
    char* getName();
protected:
    char*           m_Name ;
    Shot*           m_Sample;
    float           m_TimeBetweenShots;
    Actor*          m_Owner;
    float           m_Dt ;
    ALuint          m_FireSound;
};
#endif // PFE_WEAPON_H_
