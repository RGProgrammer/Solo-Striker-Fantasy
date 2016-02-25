#ifndef PFE_SHOT_H_
#define PFE_SHOT_H_
#include "DynamicModel.h"
class Shot: public DynamicModel{
public:
    Shot();
    Shot(Vertex3d Pos,Vertex3d Dir,Vertex3d Up );
    Shot(Actor* Source);
    Shot(Shot* clone);
    virtual ~Shot();
    virtual int LoadFromFile()=0;
    void setSource(Actor* Source);
    void setSpeed(float Speed);
    virtual int Clone(Shot* clone);
protected :
    Actor*          m_Source;
    float           m_Speed;
    int             m_Damage;
    float           m_LifeTime ;
    float           m_Time ;
};

#endif // PFE_SHOT_H_
