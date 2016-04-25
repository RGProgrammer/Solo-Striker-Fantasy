#ifndef PFE_EXPLOSION_H_
#define PFE_EXPLOSION_H_
#include "Effect.h"
class Explosion :public Effect{
public :
    Explosion();
    Explosion(Vertex3d Pos);
    Explosion(Vertex3d Pos,Vertex3d Dir, Vertex3d Up);
    Explosion(Actor* Source);
    void Update(float dt);
private:
    float       m_Speed;
    float       m_MaxScale;
};
#endif // PFE_EXPLOSION_H_
