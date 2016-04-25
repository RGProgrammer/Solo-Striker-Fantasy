#ifndef PFE_UFO_H_
#define PFE_UFO_H_
#include "Enemy.h"

class UFO :public Enemy {
public :
    UFO();
    UFO(Vertex3d Pos);
    UFO(Vertex3d Pos, Vertex3d Dir, Vertex3d Up);
    int LoadFromFile();
    int Fire(Vertex3d Direection);
};
#endif // PFE_UFO_H_
