#ifndef PFE_SCOREDISPLAY_H_
#define PFE_SCOREDISPLAY_H_
#include "StaticModel.h"
#include "GNumber.h"


class ScoreDisplay: public StaticModel{
public:
    ScoreDisplay();
    ~ScoreDisplay();
    void Destroy();
    int LoadFromFile();
    int Init();
    void GenerateDisplay(unsigned int * Scores);/// should be a vector of 5 unsigned int integers
    void Draw(float* Matrice);
private :
    GNumber**           v_GScores ;
};
#endif // PFE_SCOREDISPLAY_H_
