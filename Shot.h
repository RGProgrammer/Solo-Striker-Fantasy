#ifndef PFE_SHOT_H_
#define PFE_SHOT_H_
#include "DynamicModel.h"
//Actor ID
#define SHOT    0x0020


class Shot: public DynamicModel{
public:
    Shot();
    Shot(Vertex3d Pos,Vertex3d Dir,Vertex3d Up );
    Shot(Actor* Source);
    Shot(Shot* clone);
    virtual ~Shot();
    virtual int LoadFromFile()=0;
    virtual Shot* Clone()=0;
    virtual void Update(float dt )=0 ;
    void setSource(Actor* Source);
    void setSpeed(float Speed);
    void setDamage(int Damage);
    Actor* getSource();
    int    getDamage();
    virtual void Hit()= 0;
    float getLifeTime();
    void setLifeTime(float LifeTime);
protected :
    Actor*          m_Source;
    float           m_Speed;
    int             m_Damage;
    float           m_LifeTime ;
};

#endif // PFE_SHOT_H_
