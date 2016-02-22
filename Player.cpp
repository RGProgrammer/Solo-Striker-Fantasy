#include "Player.h"
Player::Player():DynamicModel(),m_State(NOTHING),m_Health(0),m_Charge(0){
};
Player::Player(Vertex3d Pos):DynamicModel(Pos),m_State(NOTHING),m_Health(0),m_Charge(0){
};
Player::Player(Vertex3d Pos,Vertex3d Dir,Vertex3d Up):DynamicModel(Pos,Dir,Up),
                                                        m_State(NOTHING),m_Health(0),
                                                        m_Charge(0){
};
Player::~Player(){
    DynamicModel::Destroy();
};
void Player::setScene(GameScene* Scene){
    m_Scene=Scene ;
};
