#ifndef PFE_FIRST_H_
#define PFE_FIRST_H_
#include "Boss.h"
class FIRST :public Boss {
public :
    FIRST();
    FIRST(Vertex3d Pos);
    FIRST(Vertex3d Pos,Vertex3d Dir, Vertex3d Up);
    ~FIRST();
    int LoadFromFile();
    void Destroy();
};
#endif // PFE_CUBE_H_
