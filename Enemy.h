#ifndef PFE_ENEMY_H_
#define PFE_ENEMY_H_
#include "DynamicModel.h"
#include "GameScene.h"
#include "Explosion.h"
//enemy define code
#define ENEMY       0x0010

//Enemy Actions
#define NOACTION    0x0000
#define FIREACTION  0x0001
#define MOVEACTION  0x0002
#define EXPLODE     0x0004
#define ATTACK      0x0005 //particular for Blades

//Stats
#define DEAD        0x0000
#define EXPLODING   0x0001
#define ALIVE       0x0002

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
    virtual int LoadFromFile()=0 ;
    virtual void Draw(float* ViewMtx);
    virtual void Update(float dt);
    virtual void Destroy();
    virtual int addAction(Action action);
    int Fire();
    virtual void addShotSample(Shot* Sample);
    bool isActive();
    void setActive(bool);
    void Explode();
    void getDamage(int Damage);
protected:
    int                             m_Stat ;
    int                             m_CurrentActions;
    int                             m_Health ;
    bool                            m_Active ;
    unsigned int                    m_nbActions ;
    float                           m_Dt;
    Vertex3d                        m_LastPostion;
    Shot*                           m_Sample;
    Action*                         v_Actions ;
    GameScene*                      m_Scene;
    Effect*                         m_Explosion ;
};
#endif // PFE_ENEMY_H_
