#include "LevelLoader.h"


int LevelLoader::LoadLevel(char* filename,GameScene * Scene){
    LevelLoader* levelLoader=new LevelLoader();
    int rslt=levelLoader->LoadLevelFile(filename,Scene);
    delete levelLoader;
    return rslt;
};
LevelLoader::LevelLoader():m_Sample(NULL),m_Scene(NULL){
};
LevelLoader::~LevelLoader(){
    m_Sample=NULL ;
};
int LevelLoader::LoadLevelFile(char* filename,GameScene* Scene){
    this->m_Scene=Scene ;
    char* completefilename;
    char line[250] ;

    CatStrings("Levels//",filename,&completefilename);
    FILE* lvlFile=fopen(completefilename,"r");
    if(!lvlFile)
        return 0 ;
    while(!feof(lvlFile)){
        ReadLine(lvlFile,line);
        if(contains(line,"/level"))
            DecodeLevelLine(line);
        else if(contains(line,"/skybox"))
            DecodeSkyboxLine(line);
        else if(contains(line,"/terrain"))
            DecodeTerrainLine(line);
        else if(contains(line,"/enemy"))
            DecodeEnemyLine(line);
        else if(contains(line,"/boss"))
            DecodeBossLine(line);
        else if(contains(line,"/action"))
            DecodeActionLine(line);
        else if(contains(line,"/camera"))
            DecodeCameraLine(line);
    }
    fclose(lvlFile);
    free(completefilename);
    return 1 ;
};

int LevelLoader::DecodeActionLine(char* line){
    /*Vertex3d Translate={0.0f,0.0f,0.0f},Rotate={0.0f,0.0f,0.0f};
    float inst;
    char actiontype[10];
    Action action ;
    if(m_Sample==NULL)
        return 0 ;
    if(contains(line,"param")){
        sscanf(line,"//action inst=\"%f\" type=\"%s\" param=\"%f %f %f %f %f %f\"",&inst,actiontype,
                                                &Translate.x,&Translate.y,&Translate.z,
                                                &Rotate.x,&Rotate.y,&Rotate.z);
    }

    else{
        sscanf(line,"//action inst=\"%f\" type=\"%s\"",&inst,actiontype);
    }
     action.Instance=inst;
        if(strcmp(actiontype,"MOVE")==0){
            Movement* movement=(Movement*)malloc(sizeof(Movement));
            movement->Translate=Translate;
            movement->Rotate=Rotate;
            movement->Speed=10.0f;
            action.ActionType=MOVEACTION;
            action.Data=movement ;
        }else if(strcmp(actiontype,"FIRE")==0){
            action.ActionType=MOVEACTION;
            action.Data=NULL ;
        }
        m_Sample->addAction(action);
        return 1 ;*/
};
int LevelLoader::DecodeEnemyLine(char* line){

};
int LevelLoader::DecodeBossLine(char* line){

};
int LevelLoader::DecodeTerrainLine(char* line){
   char *filename;
    char* completefilename;
    filename=ExtractString(line,"name=\"","\"");
    if(!filename)
        return 0 ;
    CatStrings("Data//",filename,&completefilename);
    Terrain* terrain=new Terrain();
    if(!terrain->LoadFromFile(completefilename))
        return 0;
    if(m_Scene->AddActor(terrain)){
        free(filename);
        free(completefilename);
        return 1;
    }else{
        free(filename);
        free(completefilename);
        return 0;
    }
};
int LevelLoader::DecodeSkyboxLine(char* line){
    char *filename;
    char* completefilename;
    filename=ExtractString(line,"name=\"","\"");
    if(!filename)
        return 0 ;
    CatStrings("Data//",filename,&completefilename);
    if(m_Scene->AddActor(StaticModel::LoadFile(completefilename))){
        free(filename);
        free(completefilename);
        return 1;
    }else{
        free(filename);
        free(completefilename);
        return 0;
    }
};
int LevelLoader::DecodeLevelLine(char* line){

};
int LevelLoader::DecodeCameraLine(char* line){

}
