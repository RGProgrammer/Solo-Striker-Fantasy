#ifndef PFE_CANON_H_
#define PFE_CANON_H_
#include "Enemy.h"

class Canon:public Enemy {
public :
    Canon();
    Canon(Vertex3d Pos);
    Canon(Vertex3d Pos ,Vertex3d Dir,Vertex3d Up);
    ~Canon();
    int LoadFromFile() ;
    void Update(float dt);
    int Fire();
};
#endif // PFE_CANON_H_
