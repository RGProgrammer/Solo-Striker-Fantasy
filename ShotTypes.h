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
class EnemyChaser: public Shot {
public:
    EnemyChaser();
    EnemyChaser(Vertex3d Pos,Vertex3d Dir,Vertex3d Up);
    EnemyChaser(Actor* Source);
    ~EnemyChaser();
    void Update(float dt);
    int LoadFromFile();
    Shot* Clone();
    void Hit();

};
class RampageShot : public Shot{
public:
    RampageShot();
    RampageShot(Vertex3d Pos,Vertex3d Dir,Vertex3d Up);
    RampageShot(Actor* Source);
    ~RampageShot();
    void Update(float dt);
    int LoadFromFile();
    Shot* Clone();
    void Hit();
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
