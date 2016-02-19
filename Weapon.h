#ifndef PFE_WEAPON_H_
#define PFE_WEAPON_H_
#include "Shot.h"
class Weapon{
public:
    Weapon(char* Name);
    Weapon(char* Name,Shot* Sample);
    void setSample(Shot* Sample);
    int Fire(GameScene* Scene,Vertex3d Pos,Vertex3d Dir,Vertex3d Up);
private:
    char*           m_Name ;
    Shot*           m_Sample;
};
#endif // PFE_WEAPON_H_
