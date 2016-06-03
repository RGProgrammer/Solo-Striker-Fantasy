#include "ScoreDisplay.h"

ScoreDisplay::ScoreDisplay():StaticModel(),v_GScores(NULL),v_GBest(NULL){};
ScoreDisplay::~ScoreDisplay(){
    this-> Destroy();
};
void ScoreDisplay::Destroy(){
    StaticModel::Destroy();
    if(v_GScores){
        for(int i=0;i<5;i++)
            if(v_GScores[i]){
                v_GScores[i]->Destroy();
                delete (v_GScores[i]) ;
            }
        free(v_GScores);
        v_GScores=NULL;
    }
    if(v_GBest){
        for(int i=0;i<5;i++)
            if(v_GBest[i]){
                v_GBest[i]->Destroy();
                delete (v_GBest[i]) ;
            }
        free(v_GBest);
        v_GBest=NULL;
    }

};
int ScoreDisplay::LoadFromFile(){
    v_GScores=(GNumber**)malloc(5*sizeof(GNumber*));
    v_GBest=(GNumber**)malloc(5*sizeof(GNumber*));
    for(int i=0 ; i<5 ;i++){
        v_GScores[i]=NULL ;
        v_GBest[i]=NULL ;
    }
    for(int i=0 ; i<5 ;i++){
        v_GScores[i]=new GNumber();
        v_GBest  [i]=new GNumber();
        v_GScores[i]->setPosition({0.0f,0.29f-i*2.1/10.0f,-4.0f});
        v_GBest  [i]->setPosition({0.5f,0.29f-i*2.1/10.0f,-4.0f});
        v_GScores[i]->setOrientation({0.0f,0.0f,-1.0f},{0.0f,1.0f,0.0f});
        v_GBest  [i]->setOrientation({0.0f,0.0f,-1.0f},{0.0f,1.0f,0.0f});
        v_GScores[i]->setScale(0.025f);
        v_GBest  [i]->setScale(0.025f);

    }
    return StaticModel::LoadFromFile("Data//DisplayBackground.obj");
};
void ScoreDisplay::GenerateDisplay(unsigned int * Current,unsigned int* Best){
    if(!Current || !Best)
        return ;
    for(int i=0 ;i<5; i++ ){
        v_GScores[i]->setValue(Current[i]);
        v_GBest  [i]->setValue(Best   [i]);
    }
};
void ScoreDisplay::Draw(float* Matrice){
    StaticModel::Draw(NULL);
    for(int i=0;i<5;i++){
        v_GScores[i]->Draw(NULL);
        v_GBest  [i]->Draw(NULL);
    }
};
