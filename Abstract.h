//////////////////////////////////////////////////////////////////////////////////////////
//                              Abstract                                                //
//this file contains bases classe that are needed in certain operations                 //
//any Classe that iherit from:                                                          //
//Drawable: should have a defined Draw() method which is used by the GraphicsEngine     //
//Updatable:should have a defined Update(param) method which is used by the GameLogic   //
//DnU: means Drawable and Updatable.
//                                                    //                                                                                      //
//////////////////////////////////////////////////////////////////////////////////////////
#ifndef PFE_INTERFACE_H_
#define PFE_INTERFACE_H_
#include "Actor.h"
//any method that is virtual and pure(=0) must be defined in the sub classes


class Drawable : public virtual Actor {
protected:
    //Constructor
    Drawable();
    Drawable(Vertex3d Pos);
    Drawable(Vertex3d Pos,Vertex3d Dir,Vertex3d Up);

public:
    //Deconstructor
    virtual ~Drawable();
    //How the model will be draw(must be defined)
    virtual void Draw(float * ViewMtx) = 0;
};
class Updatable : public virtual  Actor {
protected:
    //constructor
    Updatable();
    Updatable(Vertex3d Pos);
    Updatable(Vertex3d Pos,Vertex3d Dir,Vertex3d Up);

public:
     //Deconstructor
    virtual ~Updatable();
    //Update the models bihaviour in function of time(must be defined)
    virtual void Update(float dt) = 0;
};
class DnU : public virtual Drawable,public virtual Updatable{
protected :
    //Constructor
    DnU();
    DnU(Vertex3d Pos);
    DnU(Vertex3d Pos,Vertex3d Dir,Vertex3d Up);
    //Deconstructor
    virtual ~DnU();
public:
    virtual void Draw(float * ViewMtx) = 0;
    virtual void Update(float dt) = 0;

};
#endif // PFE_ACTOR_H_
