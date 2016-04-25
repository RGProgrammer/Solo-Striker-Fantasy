#ifndef PFE_EFFECT_H_
#define PFE_EFFECT_H_
#include "DynamicModel.h"
#define NOTSTARTED   2
#define STARTED     1
#define DONE        0

class Effect : public DynamicModel {
public :
    Effect();
    Effect(Vertex3d Pos);
    Effect(Vertex3d Pos, Vertex3d Dir, Vertex3d Up);
    Effect(Actor* Source);
    virtual void Draw(float* ViewMtx);
    void Start() ;
    void Stop() ;
    bool isStarted();
    virtual void Update(float dt)= 0;
    bool isDone();
protected :
    int             m_Stat ;
    float           m_LifeTime;
    Actor*          m_Source ;
};

#endif
