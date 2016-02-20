#ifndef PFE_BOSS_H_
#define PFE_BOSS_H_
#include "Enemy.h"
class Boss : public Enemy {
public:
    Boss();
    ~Boss();
    virtual int addbehaviour(Behaviour behav)=0;
};
#endif // PFE_BOSS_H_
