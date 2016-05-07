#ifndef PFE_SHOTTYPES_H_
#define PFE_SHOTTYPES_H_
#include "Shot.h"
//player
class EnergyBullet: public Shot{
public:
    EnergyBullet();
    EnergyBullet(Vertex3d Pos,Vertex3d Dir,Vertex3d Up);
    EnergyBullet(Actor* Source);
    ~EnergyBullet();
    void Update(float dt);
    int LoadFromFile();
    Shot* Clone();
    void Hit();
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
    SmallShot(Vertex3d Pos,Vertex3d Dir,Vertex3d Up);
    SmallShot(Actor* Source);
    ~SmallShot();
    void Update(float dt);
    int LoadFromFile();
    Shot* Clone();
    void Hit();
};
class LongShot: public Shot {
public :
    LongShot();
    LongShot(Vertex3d Pos, Vertex3d Dir, Vertex3d Up);
    LongShot(Actor* Source);
    ~LongShot();
    void Update(float dt);
    int LoadFromFile();
    Shot* Clone();
    void Hit();
};
class Laser : public Shot {
public :
    Laser();
    Laser(Vertex3d Pos, Vertex3d Dir, Vertex3d Up);
    Laser(Actor* Source);
    ~Laser();
    void Update(float dt);
    int LoadFromFile();
    Shot* Clone();
    void Hit();
};
#endif // PFE_SHOTTYPES_H_
