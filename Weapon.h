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
    virtual ~Weapon();
    virtual void Destroy();
    virtual int Fire(float dt,GameScene* Scene,Vertex3d Pos,Vertex3d Dir,Vertex3d Up)=0;
    void setSample(Shot* Sample);
    void setOwner(Actor* Owner);
    char* getName();
    StaticModel* getIcon();
protected:
    char*           m_Name ;
    Shot*           m_Sample;
    float           m_TimeBetweenShots;
    Actor*          m_Owner;
    float           m_Dt ;
    ALuint          m_FireSound;
    StaticModel*    m_Icon;
};
#endif // PFE_WEAPON_H_
