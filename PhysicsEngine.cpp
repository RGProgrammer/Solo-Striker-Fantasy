#include "PhysicsEngine.h"

PhysicsEngine::PhysicsEngine(): v_Data(NULL),m_nbElements(0),m_Scene(NULL){
};
PhysicsEngine::PhysicsEngine(GameScene* Scene):v_Data(NULL),m_nbElements(0),m_Scene(Scene){

};
PhysicsEngine::~PhysicsEngine(){
    if(v_Data){
        free(v_Data);
        v_Data==NULL;
    }
};
void PhysicsEngine::setScene(GameScene* Scene){
    m_Scene=Scene ;
};
void PhysicsEngine::CollisioDetection(){
    //all collison in the Scene btween Physical Actorss
};
void PhysicsEngine::CollisionReaction(){
    //reaction depends the Type of the Actor (player,enemy,Shot)
};
int PhysicsEngine::AddData(CollisionData data){

};
