#ifndef PFE_PLAYERSTATUS_H_
#define PFE_PLAYERSTATUS_H_
#include "StaticModel.h"
class PlayerStatus : public StaticModel{
public :
    PlayerStatus();
    ~PlayerStatus();
    void Destroy();
    int LoadFromFile();
    void Draw(float * Matrix);
    void  setIcon(StaticModel* Icon);
    int getShieldValue();
    void setShieldValue(int Value);
private:
    int                 m_Shield;
    StaticModel*        m_Icon;
    StaticModel*        m_ShIconSample;
};

#endif // PFE_PLAYERSTATUS_H_
