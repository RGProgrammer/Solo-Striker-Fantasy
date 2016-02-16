#ifndef PFE_ENEMY_H_
#define PFE_ENEMY_H_
#include "DynamicModel.h"
#include "GameScene.h"
//Comment action
#define ROTATION

typedef struct {
    int ActionCode;
    float Instance;
} Behaviour;
class Enemy: public DynamicModel{
public :
    Enemy();
    Enemy(Vertex3d Pos);
    Enemy(Vertex3d Pos,Vertex3d Dir,Vertex3d Up);
    virtual ~Enemy();
    void setScene(GameScene* Scene);
    virtual void Update(float dt)=0;
    virtual void Destroy();
protected:
    unsigned int                    m_nbBehaviours ;
    Behaviour*                      v_Behaviours ;
    GameScene*                      m_Scene;
};
#endif // PFE_ENEMY_H_
