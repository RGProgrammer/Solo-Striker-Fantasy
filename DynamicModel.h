#ifndef PFE_DYNAMICMODEL_H_
#define PFE_DYNAMICMODEL_H_
#include "StaticModel.h"
#include "Abstract.h"
class DynamicModel:public StaticModel,public Updatable{
public:
    DynamicModel();
    DynamicModel(Vertex3d Pos);
    DynamicModel(Vertex3d Pos,Vertex3d Dir,Vertex3d Up);
    ~DynamicModel();
    virtual void Destroy();
    virtual int Clone(DynamicModel * Model);
protected:
    Vertex3d                m_Velocity;
    float                   m_Dt;
};
#endif // PFE_DYNAMICMODEL_H_
