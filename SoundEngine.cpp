#include "SoundEngine.h"

 SoundEngine::SoundEngine(): m_Music(NULL), m_MusicRepeat(false),m_nbSounds(0),
                                v_Sounds(NULL),v_Sources(NULL),m_Listener(NULL){
 };
SoundEngine::~SoundEngine(){
    Destroy();
};
void SoundEngine::PlaySound(Sound* sound ,Actor* source){

};
void SoundEngine::PlayMusic(Sound* Music,bool repeat){

};
void SoundEngine::Destroy(){
    if(m_Music){
        free(m_Music);
        m_Music=NULL ;
    }
    if(v_Sounds){
        free(v_Sounds);
        v_Sounds=NULL ;
    }
    if(v_Sources){
        free(v_Sources);
        v_Sources=NULL ;
    }
    m_Listener=NULL;
};
Sound* SoundEngine::LoadfromFile(char* filename){
    Sound* sound=NULL;
    FILE* File=fopen(filename,"rb");
    //read fie precess here

    fclose(File);
    return sound ;
};
