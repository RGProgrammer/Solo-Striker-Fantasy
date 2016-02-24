/////////////////////////////////////////////////////////////////////////////////////
//                              Actor                                              //
//this classe represent the base classe of any object that could be inserted in    //
//the GameScene                                                                    //
//                                                                                 //
/////////////////////////////////////////////////////////////////////////////////////
#ifndef PFE_ACTOR_H_
#define PFE_ACTOR_H_
#include "Math.h"
#include <stdlib.h>

//IDs for the Actor type

#define UNKNOWN     0x0000
#define DRAWABLE    0x0001
#define UPDATABLE   0x0002
#define LIGHT       0x0004
#define PHYSICAL    0x0008


class Actor{
protected:
    //Constructors
    Actor();
    Actor(Vertex3d Pos);
    Actor(Vertex3d Pos,Vertex3d Dir,Vertex3d Up);
public :
    //Deconstructor
    ~Actor() ;
    //Free Resources
    virtual void Destroy() ;
    //get Actor type
    int getID();
    //return transformaion matrix
    virtual float* getTransMtx();
    //set Orientation orientation of the Modl:Direction , Up vertices
    int setOrientation(Vertex3d,Vertex3d);
    //Set model Position in 3d space
    void setPosition(Vertex3d);
    //getters
    Vertex3d getDirection();
    Vertex3d getPosition();
    Vertex3d getUp();
    Vertex3d getRight();
    //translate the model postion  by a vertex
    void Translate(Vertex3d );
    //rotate the model by the Up Vertex
    void RotateViaUp(float);
    //rotate the model by the Direction Vertex
    void RotateViaDirection(float);
    //rotate the model by the Right Vertex
    void RotateViaRight(float);
protected:
    virtual void UpdateMtx();  //set transformation matrix fields values
    int                 m_ID ; // Actor type
    Vertex3d            m_Pos,m_Dir,m_Up,m_Right ;// position and orientaion of the actor in 3d Space
    float*              m_TransMtx ;//transformation matrix
};
#endif // PFE_ACTOR_H_
