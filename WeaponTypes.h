#ifndef PFE_WEAPONTYPES_H_
#define PFE_WEAPONTYPES_H_
#include "Weapon.h"
#include "ShotTypes.h"
//player Weapons
class MachineGun :public Weapon {
public :
    MachineGun(Actor* Owner);
    ~MachineGun();
    int Fire(GameScene* Scene,Vertex3d Pos,Vertex3d Dir,Vertex3d Up);

};
class ChaserLauncher: public Weapon{
public :
    ChaserLauncher();
    ~ChaserLauncher();
};


//enemies weapons

#endif // PFE_WEAPONTYPES_H_
