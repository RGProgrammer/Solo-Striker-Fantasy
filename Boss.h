#ifndef PFE_BOSS_H_
#define PFE_BOSS_H_
#include "Enemy.h"
#define BOSS        0x0080
class Boss : public Enemy {
public:
    Boss();
    Boss(Vertex3d Pos);
    Boss(Vertex3d Pos,Vertex3d Dir,Vertex3d Up);
    virtual int LoadFromFile()=0;
    virtual ~Boss();
};
#endif // PFE_BOSS_H_
