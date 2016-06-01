#ifndef PFE_CREDITHANDLER_H_
#define PFE_CREDITHANDLER_H_
#include "StaticModel.h"
#include "GNumber.h"
class CreditHandler : public StaticModel {
public:
    CreditHandler();
    ~CreditHandler();
    void Destroy();
    int Init(unsigned int value);
    void Draw(float* Matrix);
    void setCreditValue(unsigned int Value);
    int getCredit();
    void MinusOne();
private:
    unsigned int        m_Credit;
    GNumber*            m_GValue;

};
#endif // PFE_CREDITHANDLER_H_
