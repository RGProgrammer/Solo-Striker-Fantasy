#include "Player.h"
Player::Player():DynamicModel(),m_State(NOTHING){
};
Player::Player(Vertex3d Pos):DynamicModel(Pos),m_State(NOTHING){
};
Player::Player(Vertex3d Pos,Vertex3d Dir,Vertex3d Up):DynamicModel(Pos,Dir,Up),m_State(NOTHING){
};
Player::~Player(){
    DynamicModel::Destroy();
};
int Player::LoadFromFile(){
//the important part
return 1 ;
};
void Player::Update(float dt){

};
void Player::Update(SDL_Event event){

};
