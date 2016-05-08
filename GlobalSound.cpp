#include "GlobalSound.h"


int CreateGlobalSoundEngine(){
    GlobalSoundHandler=new SoundEngine();
    if(!GlobalSoundHandler){
        return 0 ;}
    if(!GlobalSoundHandler->InitEngine()){
        delete GlobalSoundHandler ;
        GlobalSoundHandler=NULL ;
        return 0;
    }
    return 1 ;
};
void DestroyGlobalSoundEngine(){
    if(GlobalSoundHandler){
        GlobalSoundHandler->Destroy();
        delete GlobalSoundHandler ;
        GlobalSoundHandler=NULL ;
    }
};
SoundEngine* getGlobalSoundEngineInstance(){
    return GlobalSoundHandler ;
};
