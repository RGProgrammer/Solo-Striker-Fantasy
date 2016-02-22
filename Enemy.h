#ifndef PFE_ENEMY_H_
#define PFE_ENEMY_H_
#include "DynamicModel.h"
#include "GameScene.h"
#define ENEMY       0x0010

typedef struct {
    Vertex3d    Translate; //add this vertex to the Position
    Vertex3d    Rotate ;  //each attribut represent the angle of rotation on each axe(Direction,Up,right)
    float       Speed; // when to start / delay
}  Movement ;
typedef struct {
    int  ActionType; // shooting or moving
    void * Data;//a pointer on the actiontype data
    float Instance ;// when to start the action /Delay
} Action;

//Base class represents any enemy in the game Scene
class Enemy: public DynamicModel{
public :
    Enemy();
    Enemy(Vertex3d Pos);
    Enemy(Vertex3d Pos,Vertex3d Dir,Vertex3d Up);
    virtual ~Enemy();
    void setScene(GameScene* Scene);
    virtual void Update(float dt)=0;
    virtual void Destroy();
    virtual int addAction(Action action);
protected:
    unsigned int                    m_nbActions ;
    Action*                         v_Actions ;
    GameScene*                      m_Scene;
};
#endif // PFE_ENEMY_H_
