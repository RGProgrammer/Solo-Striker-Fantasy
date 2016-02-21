#ifndef PFE_BOSS_H_
#define PFE_BOSS_H_
#include "Enemy.h"
class Boss : public Enemy {
protected:
    Boss();
    Boss(Vertex3d Pos);
    Boss(Vertex3d Pos,Vertex3d Dir,Vertex3d Up);
public:
    ~Boss();
};
#endif // PFE_BOSS_H_
