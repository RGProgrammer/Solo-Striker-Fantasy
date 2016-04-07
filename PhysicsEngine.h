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
    bool CollisionCheck(StaticModel* obj1,StaticModel* obj2,Vertex3d* CollisionCenter);
    int AddData(CollisionData data);
    void FreeData();
    CollisionData*              v_Data;
    unsigned int                m_nbElements ;
    GameScene*                  m_Scene ;
    float                       m_Dt ;

};
#endif // PFE_PHYSICSENGINE_H_
