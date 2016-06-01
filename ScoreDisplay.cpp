#include "ScoreDisplay.h"

ScoreDisplay::ScoreDisplay():StaticModel(),v_GScores(NULL){};
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

};
int ScoreDisplay::LoadFromFile(){
    v_GScores=(GNumber**)malloc(5*sizeof(GNumber*));
    for(int i=0 ; i<5 ;i++){
        v_GScores[i]=NULL ;
    }
    for(int i=0 ; i<5 ;i++){
        v_GScores[i]=new GNumber();
    }
    return StaticModel::LoadFromFile("Data//DisplayBackground.obj");
};
void ScoreDisplay::GenerateDisplay(unsigned int *Scores){
    if(!Scores)
        return ;
    for(int i=0 ;i<5; i++ ){
        v_GScores[i]->setValue(Scores[i]);
    }
};
void ScoreDisplay::Draw(float* Matrice){
    StaticModel::Draw(NULL);
    for(int i=0;i<5;i++){
        v_GScores[i]->Draw(NULL);
    }
};
