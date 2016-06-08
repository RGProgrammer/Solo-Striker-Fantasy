#ifndef PFE_BLADES_H_
#define PFE_BLADES_H_
#include "Enemy.h"
class Blades : public Enemy{
public :
    Blades();
    Blades(Vertex3d Pos);
    Blades(Vertex3d Pos ,Vertex3d Dir,Vertex3d Up );
    ~Blades();
    int LoadFromFile();
    void Update(float dt);
    int Clone(Blades* Clone);
};
#endif // PFE_BLADES_H_
