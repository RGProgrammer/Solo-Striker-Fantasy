#ifndef PFE_AEX2_H_
#define PFE_AEX2_H_
#include "Enemy.h"

class AEX2 : public Enemy {
public :
    AEX2();
    AEX2(Vertex3d Pos);
    AEX2(Vertex3d Pos, Vertex3d Dir,Vertex3d Up);
    ~AEX2();
    int LoadFromFile();
    void Update(float dt);
    int Clone(AEX2* Clone);
};
#endif // PFE_AEX2_H_
