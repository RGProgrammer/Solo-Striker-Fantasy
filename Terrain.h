#ifndef PFE_TERRAIN_H_
#define PFE_TERRAIN_H_
#include "StaticModel.h"
class Terrain : public DnU{
public:
    Terrain();
    ~Terrain();
    void Destroy();
    int LoadFromFile(char* filename);
    void setSpeed(float Speed );
    void Update(float dt);
    void Draw(float* ViewMtx);
private:
    StaticModel*        m_Sample ;
    Vertex3d*           v_Points;
    float               m_Speed ;
};
#endif // PFE_TERRAIN_H_4
