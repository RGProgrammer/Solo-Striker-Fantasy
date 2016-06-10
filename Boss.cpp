#include "Boss.h"
Boss::Boss():Enemy(){
    m_ID |= BOSS;
};
Boss::Boss(Vertex3d Pos):Enemy(Pos){
    m_ID |= BOSS;
};
Boss::Boss(Vertex3d Pos,Vertex3d Dir,Vertex3d Up):Enemy(Pos,Dir,Up){
    m_ID |= BOSS;
};
Boss::~Boss(){
    Enemy::Destroy();
};
