#ifndef PFE_WEAPONTYPES_H_
#define PFE_WEAPONTYPES_H_
#include "Enemy.h"
#include "Weapon.h"
#include "ShotTypes.h"
//player Weapons
class MachineGun :public Weapon {
public :
    MachineGun(Actor* Owner);
    ~MachineGun();
    int Fire(float dt,GameScene* Scene,Vertex3d Pos,Vertex3d Dir,Vertex3d Up);

};
class Rampage : public Weapon{
public:
    Rampage(Actor* Owner);
    ~Rampage();
    int Fire(float dt, GameScene* Scene,Vertex3d Pos,Vertex3d Dir,Vertex3d Up);
private:
    float           m_MaxRotation;
};

class EnemyChaserLauncher:public Weapon {
public:
    EnemyChaserLauncher(Actor* Owner);
    ~EnemyChaserLauncher();
    int Fire(float dt,GameScene* Scene,Vertex3d Pos, Vertex3d Dir,Vertex3d Up);
private:
    Enemy*          m_Target ;
};


//enemies weapons

#endif // PFE_WEAPONTYPES_H_
