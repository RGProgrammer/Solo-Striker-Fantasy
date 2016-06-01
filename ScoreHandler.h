#ifndef PFE_SCOREHANDLER_H_
#define PFE_SCOREHANDLER_H_
#include "StaticModel.h"
#include "GNumber.h"
class ScoreHandler: public StaticModel {
public:
    ScoreHandler();
    ScoreHandler(Vertex3d Pos);
    ScoreHandler(Vertex3d Pos,Vertex3d Dir,Vertex3d Up);
    ~ScoreHandler();
    void Destroy();
    int LoadFromFile();
    void setValue(unsigned int Score);
    unsigned int getValue();
    void AddValue(unsigned int Value);
    void Draw(float* Matrix);   ///4x4 matrix
private:
    GNumber*       m_NumberHandler;
};
#endif // PFE_SCOREHANDLER_H_
