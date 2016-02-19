#ifndef PFE_WEAPONTYPES_H_
#define PFE_WEAPONTYPES_H_
#include "Weapon.h"
#include "ShotTypes.h"
//player Weapons
class MachineGun :public Weapon {
public :
    MachineGun();
    ~MachineGun();

};
class ChaserLauncher: public Weapon{
public :
    ChaserLauncher();
    ~ChaserLauncher();
};


//enemies weapons

#endif // PFE_WEAPONTYPES_H_
