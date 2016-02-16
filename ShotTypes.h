#ifndef PFE_SHOTTYPES_H_
#define PFE_SHOTTYPES_H_
#include "Shot.h"
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
#endif // PFE_SHOTTYPES_H_
