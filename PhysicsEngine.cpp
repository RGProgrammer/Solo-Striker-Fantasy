#include "PhysicsEngine.h"
#include <stdio.h>

PhysicsEngine::PhysicsEngine():PhysicsEngine(NULL){ //v_Data(NULL),m_nbElements(0),m_Scene(NULL){
};
PhysicsEngine::PhysicsEngine(GameScene* Scene):v_Data(NULL),m_nbElements(0),m_Scene(Scene),m_Dt(0.0f){
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
        unsigned int nbActors=m_Scene->getNBActors();
        Vertex3d CollisionCenter ;
        StaticModel* tmp1,*tmp2;
        if(nbActors>0)
        for(unsigned int i=0; i<nbActors-1;i++){
            if(m_Scene->getActor(i)->getID() & PHYSICAL){
                tmp1=dynamic_cast<StaticModel*>(m_Scene->getActor(i));
                for(unsigned int j=i+1;j<nbActors;j++)
                    if(m_Scene->getActor(j)->getID() & PHYSICAL){
                        tmp2=dynamic_cast<StaticModel*>(m_Scene->getActor(j));
                        if(CollisionCheck(tmp1,tmp2,&CollisionCenter)){
                            AddData({tmp1,tmp2,CollisionCenter});
                        }
                    }
            }
        }
};
void PhysicsEngine::CollisionReaction(){
    for(unsigned int i = 0;i<m_nbElements;i++){

        //check for collision between enmy anf Player's Shots
        if((v_Data[i].Object1->getID() & ENEMY) && (v_Data[i].Object2->getID() & SHOT)){
            if(((Shot*)(v_Data[i].Object2))->getSource()==NULL || ((Shot*)(v_Data[i].Object2))->getSource()->getID() & PLAYER ){
                ((Enemy*)(v_Data[i].Object1))->getDamage(((Shot*)(v_Data[i].Object2))->getDamage());
                ((Shot*)(v_Data[i].Object2))->Hit();
            }
        }
        if((v_Data[i].Object1->getID() & SHOT) && (v_Data[i].Object2->getID() & ENEMY)){
            if(((Shot*)(v_Data[i].Object1))->getSource()==NULL || ((Shot*)(v_Data[i].Object1))->getSource()->getID() & PLAYER ){
                ((Enemy*)(v_Data[i].Object2))->getDamage(((Shot*)(v_Data[i].Object1))->getDamage());
                ((Shot*)(v_Data[i].Object1))->Hit();
            }
        }
    }
    FreeData();
};
bool PhysicsEngine::CollisionCheck(StaticModel* obj1,StaticModel* obj2,Vertex3d* CollisionCenter){
    //using AABBs
    Vertex3d MinVertex1,MaxVertex1 ;
    Vertex3d MinVertex2,MaxVertex2 ;
    obj1->getAABB(&MinVertex1,&MaxVertex1); obj2->getAABB(&MinVertex2,&MaxVertex2);
    if(MinVertex1.x<MaxVertex2.x && MaxVertex1.x> MinVertex2.x &&
       MinVertex1.y<MaxVertex2.y && MaxVertex1.y> MinVertex2.y &&
       MinVertex1.z<MaxVertex2.z && MaxVertex1.z> MinVertex2.z ){
        return true ;
    }
    //using sphere
    /*float radius1=obj1->getRadius(),radius2=obj2->getRadius() ;
    Vertex3d Pos1=obj1->getPosition(),Pos2=obj2->getPosition() ;
    if(Magnitude3d(SubsVertex3d(Pos2,Pos1))<radius1+radius2){
        return true ;
    }*/
    return false ;
};
int PhysicsEngine::AddData(CollisionData data){
    CollisionData* tmp=(CollisionData*)malloc((m_nbElements+1)*sizeof(CollisionData));
    if(!tmp)
        return 0 ;
    for(unsigned int i=0;i<m_nbElements;i++)
        tmp[i]=v_Data[i];
    if(v_Data){
        free(v_Data);
        v_Data=NULL;
    }
    v_Data=tmp ;
    v_Data[m_nbElements]=data ;
    m_nbElements++;
    return 1 ;
};
void PhysicsEngine::FreeData(){
    if(v_Data){
        free(v_Data);
        v_Data=NULL;
        m_nbElements=0;
    }
    m_nbElements=0;
};

