#ifndef PFE_CAMERA_H_
#define PFE_CAMERA_H_
#include "Actor.h"
class Camera : public Actor {
public:
    Camera();
    ~Camera();
    //void printInfo();
protected:
    void UpdateMtx();
};
#endif // PFE_CAMERA_H_
