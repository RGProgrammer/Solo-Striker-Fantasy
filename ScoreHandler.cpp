#include "ScoreHandler.h"

ScoreHandler::ScoreHandler(): ScoreHandler({0.0f,0.0f,0.0f})
{};
ScoreHandler::ScoreHandler(Vertex3d Pos):ScoreHandler(Pos,{0.0f,0.0f,-1.0f},{0.0f,1.0f,0.0f}){};
ScoreHandler::ScoreHandler(Vertex3d Pos,Vertex3d Dir,Vertex3d Up):StaticModel(Pos,Dir,Up),m_NumberHandler(NULL){

};
ScoreHandler::~ScoreHandler(){
    this->Destroy();
};
void ScoreHandler::Destroy(){
    StaticModel::Destroy();
    if(m_NumberHandler){
        m_NumberHandler->Destroy();
        delete m_NumberHandler;
        m_NumberHandler=NULL;
    }
};
int ScoreHandler::LoadFromFile(){
    m_NumberHandler=new GNumber();
    m_NumberHandler->setScale(0.1f);
    Scale(0.3);
    setPosition({-4.1f,3.9f,-10.0f});
    return StaticModel::LoadFromFile("Data//ScoreBar.obj");
};
void ScoreHandler::setValue(unsigned int Score){
    m_NumberHandler->setValue(Score);
};
unsigned int ScoreHandler::getValue(){
    return m_NumberHandler->getValue();
};
void ScoreHandler::AddValue(unsigned int Value){
    m_NumberHandler->AddValue(Value);
};
void ScoreHandler::Draw(float* Matrix){
    StaticModel::Draw(Matrix);
    m_NumberHandler->setPosition(AddVertex3d(this->getPosition(),{0.0f,0.0f,0.01f}));
    m_NumberHandler->setOrientation(this->getDirection(),this->getUp());
    m_NumberHandler->Draw(Matrix);

};
