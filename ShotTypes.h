#ifndef PFE_SHOTTYPES_H_
#define PFE_SHOTTYPES_H_
#include "Shot.h"
//player
class EnergyBullet: public Shot{
public:
    EnergyBullet();
    ~EnergyBullet();
};
class Chaser: public Shot {
public:
    Chaser();
    ~Chaser();
};
//enemies
class SmallShot : public Shot {
public :
    SmallShot();
    ~SmallShot();
};
class LongShot: public Shot {
public :
    LongShot();
    ~LongShot();
};
#endif // PFE_SHOTTYPES_H_
