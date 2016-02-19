#ifndef PFE_WEAPON_H_
#define PFE_WEAPON_H_
#include "Shot.h"
#include "GameScene.h"
class Weapon{
public:
    Weapon(char* Name);
    Weapon(char* Name,Shot* Sample);
    void setSample(Shot* Sample);
    virtual int Fire(GameScene* Scene,Vertex3d Pos,Vertex3d Dir,Vertex3d Up)=0;
    char* getName();
private:
    char*           m_Name ;
    Shot*           m_Sample;
};
#endif // PFE_WEAPON_H_
