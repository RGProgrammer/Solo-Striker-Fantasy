#include "Player.h"
Player::Player():DynamicModel(),m_Stat(NOTHING),m_Health(0),m_Charge(0),
                    m_Camera(NULL),m_Score(NULL){
    m_ID|= PLAYER |PHYSICAL ;
};
Player::Player(Vertex3d Pos):DynamicModel(Pos),m_Stat(NOTHING),m_Health(0),
                            m_Charge(0),m_Camera(NULL),m_Score(NULL){
     m_ID|= PLAYER |PHYSICAL ;
};
Player::Player(Vertex3d Pos,Vertex3d Dir,Vertex3d Up):DynamicModel(Pos,Dir,Up),
                                                        m_Stat(NOTHING),m_Health(0),
                                                        m_Charge(0),m_Camera(NULL),
                                                        m_Score(NULL){
    m_ID|= PLAYER |PHYSICAL ;
};
Player::~Player(){
    m_Camera=NULL ;
    m_Scene=NULL ;
    if(m_Score){
        m_Score->Destroy();
        delete m_Score ;
        m_Score=NULL ;
    }
    DynamicModel::Destroy();
};
void Player::setScene(GameScene* Scene){
    m_Scene=Scene ;
};
void Player::setCamera(Camera* Cam){
    m_Camera=Cam;
};
void Player::getDamage(){
    if(m_Stat!=DEAD){
        m_Health--;
        if(m_Health<=0)
            m_Stat=DEAD;
    }
};
void Player::setScore(unsigned int Score){
    if(m_Score){
        m_Score->setValue(Score);
    }
};
unsigned int Player::getScore(){
    if(m_Score){
        return m_Score->getValue();
    }else
        return 0 ;
};
void Player::AddtoScore(unsigned int Value){
    if(m_Score){
        m_Score->AddValue(Value);
    }
};
