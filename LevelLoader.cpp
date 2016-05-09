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
    char line[300] ;

    CatStrings("Levels//",filename,&completefilename);
    FILE* lvlFile=fopen(completefilename,"r");
    if(!lvlFile)
        return 0 ;
    while(!feof(lvlFile)){
        ReadLine(lvlFile,line);
        if(contains(line,"/skybox"))
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
        else if(contains(line,"/music"))
            DecodeMusicLine(line);
    }
    fclose(lvlFile);
    free(completefilename);
    return 1 ;
};

int LevelLoader::DecodeActionLine(char* line){
    float value;
    Action action;
    char* tmpstr=NULL ;
    if(contains(line,"inst=")){
        tmpstr=ExtractString(line,"inst=\"","\"");
        sscanf(tmpstr,"%f",&value);
        action.Instance=value;
        action.ActionType=NOACTION;
        action.Data=NULL;
    }
    if(contains(line,"type=")){
        tmpstr=ExtractString(line,"type=\"","\"");
        if(strcmp(tmpstr,"MOVE")==0){
            action.ActionType=MOVEACTION;
            free(tmpstr);
            if(contains(line,"param=")){
                Movement* movement=(Movement*)malloc(sizeof(Movement));
                tmpstr=ExtractString(line,"param=\"","\"");
                sscanf(tmpstr,"%f %f %f %f %f %f",&(movement->Translate.x),&(movement->Translate.y),&(movement->Translate.z),
                                           &(movement->Rotate.x),&(movement->Rotate.y),&(movement->Rotate.z));
                movement->Speed=0.7f;
                action.Data=movement;
                m_Sample->addAction(action);
                free(tmpstr);
                if(contains(line,"speed=")){
                    tmpstr=ExtractString(line,"speed=\"","\"");
                    sscanf(tmpstr,"%f",&(movement->Speed));
                }
            }

        }else if(strcmp(tmpstr,"FIRE")==0){
            action.ActionType=FIREACTION;
            free(tmpstr);
            if(contains(line,"param=")){
                Vertex3d* dir=(Vertex3d*)malloc(sizeof(Vertex3d));
                tmpstr=ExtractString(line,"param=\"","\"");
                sscanf(tmpstr,"%f %f %f",&dir->x,&dir->y,&dir->z);
                free(tmpstr);
                action.Data=dir;
            }
            m_Sample->addAction(action);
        }else if(strcmp(tmpstr,"EXPLODE")==0){
            action.ActionType=EXPLODE;
            m_Sample->addAction(action);
        }else if(strcmp(tmpstr,"KILL")==0){
            action.ActionType=KILL;
            m_Sample->addAction(action);
        }
    }
};
int LevelLoader::DecodeEnemyLine(char* line){
    Vertex3d ver1,ver2;
    char* tmpstr=NULL;
    if(contains(line,"type=")){
        tmpstr=ExtractString(line,"type=\"","\"");
        if(strcmp(tmpstr,"UFO")==0){
            m_Sample=new UFO();
            m_Sample->setScene(m_Scene);
            m_Sample->LoadFromFile();
            m_Scene->AddActor(m_Sample);
        }else if(strcmp(tmpstr,"Blades")==0){
            m_Sample=new Blades();
            m_Sample->setScene(m_Scene);
            m_Sample->LoadFromFile();
            m_Scene->AddActor(m_Sample);
        }else if(strcmp(tmpstr,"Canon")==0){
             m_Sample=new Canon();
             m_Sample->setScene(m_Scene);
            m_Sample->LoadFromFile();
            m_Scene->AddActor(m_Sample);
        }
        if(tmpstr){
            free(tmpstr);
            tmpstr=NULL;
        }
        if(contains(line,"shot=\"")){
            Shot* shotsample =NULL ;
            tmpstr=ExtractString(line,"shot=\"","\"");
            if(strcmp(tmpstr,"Small")==0){

            }else if(strcmp(tmpstr,"Long")==0){
                shotsample=new LongShot(m_Sample);
                shotsample->LoadFromFile();
                m_Sample->addShotSample(shotsample);
            }else if(strcmp(tmpstr,"Chaser")==0){

            }else if(strcmp(tmpstr,"Laser")==0){
                shotsample=new Laser(m_Sample);
                shotsample->LoadFromFile();
                m_Sample->addShotSample(shotsample);
            }
        }
        if(tmpstr){
            free(tmpstr);
            tmpstr=NULL;
        }
    }else{
        return 0 ;
    }
    if(contains(line,"pos=")){
        tmpstr=ExtractString(line,"pos=\"","\"");
        sscanf(tmpstr,"%f %f %f",&ver1.x,&ver1.y,&ver1.z);
        m_Sample->setPosition(ver1);
        if(tmpstr){
            free(tmpstr);
            tmpstr=NULL;
        }
    }if(contains(line,"dir")){
        tmpstr=ExtractString(line,"dir=\"","\"");
        sscanf(tmpstr,"%f %f %f",&ver1.x,&ver1.y,&ver1.z);
        free(tmpstr);
        tmpstr=ExtractString(line,"up=\"","\"");
        sscanf(tmpstr,"%f %f %f",&ver2.x,&ver2.y,&ver2.z);
        free(tmpstr);
        m_Sample->setOrientation(ver1,ver2);
    }
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
int LevelLoader::DecodeCameraLine(char* line){
    Camera* Cam=m_Scene->getCamera() ;
    char* tmpstr=NULL;
    if(Cam==NULL)
        return 0 ;
    tmpstr=ExtractString(line,"type=\"","\"");
    if(strcmp(tmpstr,"SIDE")==0){
        Cam->setViewType(SIDE);
    }
    else if(strcmp(tmpstr,"UP")==0){
        Cam->setViewType(UP);
    }
    free(tmpstr);
}
int LevelLoader::DecodeMusicLine(char* line){
    Sound* Music=NULL ;
    char* tmpstr=NULL ;
    char* filename ;
    if(contains(line,"name=")){
        tmpstr=ExtractString(line,"name=\"","\"");
        CatStrings("Sound//",tmpstr,&filename);
        Music=SoundEngine::LoadWAVFile(filename);
        free(tmpstr);
        free(filename);
        filename=NULL ;
        tmpstr=NULL;
        if(!Music){
            return 0 ;}
        getGlobalSoundEngineInstance()->LoadMusic(Music,true);
        free(Music->Buffer);
        free(Music);
        Music=NULL;
    }
    return 1 ;
};
