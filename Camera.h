#ifndef PFE_CAMERA_H_
#define PFE_CAMERA_H_
#include "Actor.h"

enum ORIENTATION{
    FREE=1,
    SIDE=2,
    UP=3
};

class Camera : public Actor {
public:
    Camera();
    ~Camera();
    int getViewType();
    void setViewType(int Type);
    void printInfo();
protected:
    void UpdateMtx();
    int         m_ViewType ;

};
#endif // PFE_CAMERA_H_
