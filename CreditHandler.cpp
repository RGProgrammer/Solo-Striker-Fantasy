#include "CreditHandler.h"

CreditHandler::CreditHandler():StaticModel(),m_Credit(0),m_GValue(NULL){
};
CreditHandler::~CreditHandler(){
    this->Destroy();
};
void CreditHandler::Destroy(){
    StaticModel::Destroy();
    if(m_GValue){
        m_GValue->Destroy();
        delete m_GValue;
        m_GValue=NULL ;
    }
};
int CreditHandler::Init(unsigned int value){
    if(value > 12)
        m_Credit=12;
    else
        m_Credit=value;
    m_GValue= new GNumber();
    m_GValue->setNBDigits(2);
    m_GValue->setValue(m_Credit);
    setPosition({0.0f,0.0f,-4.f});
    setOrientation({0.0f,0.0f,-1.0f},{0.0f,1.0f,0.0f});
    m_GValue->setPosition({0.0f,0.12f,-4.0f});
    m_GValue->setOrientation({0.0f,0.0f,-1.0f},{0.0f,1.0f,0.0f});
    m_GValue->setScale(0.022f);
    return StaticModel::LoadFromFile("Data//CreditHandler.obj");
};
void CreditHandler::Draw(float* Matrix){
    StaticModel::Draw(NULL);
    m_GValue->Draw(NULL);
};
void CreditHandler::setCreditValue(unsigned int value){
     if(value > 12)
        m_Credit=12;
    else
        m_Credit=value;
    m_GValue->setValue(m_Credit);
};
int CreditHandler::getCredit(){
    return m_Credit ;
};
void CreditHandler::MinusOne(){
    m_Credit-- ;
    m_GValue->setValue(m_Credit);
};
