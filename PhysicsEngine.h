#ifndef PFE_PHYSICSENGINE_H_
#define PFE_PHYSICSENGINE_H_
#include "GameScene.h"
#include "Player.h"
#include "Enemy.h"
#include "Shot.h"
#include "Math.h"

typedef struct {
    StaticModel*  Object1;
    StaticModel*  Object2;
    Vertex3d       Center;

} CollisionData ;
class PhysicsEngine{
public :
    PhysicsEngine();
    PhysicsEngine(GameScene* Scene);
    ~PhysicsEngine();
    void setScene(GameScene* Scene);
    void CollisioDetection();
    void CollisionReaction();
private:
    int AddData(CollisionData data);
    CollisionData*              v_Data;
    unsigned int                m_nbElements ;
    GameScene*                  m_Scene ;

};
#endif // PFE_PHYSICSENGINE_H_
