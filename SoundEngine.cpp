#include "SoundEngine.h"

SoundEngine::SoundEngine():m_Device(NULL) ,m_Context(NULL),m_MusicBuffer(0),m_MusicSource(0),m_MusicStatus(SSTOP),
                            m_Repeat(false),m_nbSounds(0),v_Sounds(NULL),v_Sources(NULL){};
SoundEngine::~SoundEngine(){
    this->Destroy();
};
int SoundEngine::InitEngine(){
    m_Device=alcOpenDevice(NULL);
    if(!m_Device){
        return 0 ;
    }
    m_Context=alcCreateContext(m_Device,NULL);
    if(!m_Context){
        return 0 ;
    }
    alcMakeContextCurrent(m_Context);
    alcProcessContext(m_Context);
    return 1 ;
};
void SoundEngine::Destroy(){
    ReleaseBuffers();
    if(m_MusicSource){
        alDeleteSources(1,&m_MusicSource);
        m_MusicSource=0 ;
    }
    if(m_MusicBuffer){
        alDeleteBuffers(1,&m_MusicBuffer);
        m_MusicBuffer=0 ;
    }
    if(m_Context){
        alcDestroyContext(m_Context);
        m_Context=NULL ;
    }
    if(m_Device){
        alcCloseDevice(m_Device);
        m_Device=NULL ;
    }
};
void SoundEngine::setListener(Actor* Listener){
    Vertex3d  ver1,ver2;
    if(!Listener){
        Vertex3d  ver1,ver2;
        ver1=Listener->getDirection();
        ver2=Listener->getUp();
        ALfloat tab[6]={ver1.x,ver1.y,ver1.z,ver2.x,ver2.y,ver2.z};
        ver1=Listener->getPosition();
        alListener3f(AL_POSITION,ver1.x,ver1.y,ver1.z);
        alListenerfv(AL_ORIENTATION,tab);
    }else{
        ALfloat tab[6]={0.0f,0.0f,-1.0f,0.0f,1.0f,0.0f};
        alListener3f(AL_POSITION,0.0f,0.0f,0.0f);
        alListenerfv(AL_ORIENTATION,tab);
    }
};
ALuint SoundEngine::LoadSound(Sound sound){
    ALuint IDSound=0,IDSource=0 ;
    alGenBuffers(1,&IDSound);
    if(!IDSound)
        return 0 ;
    alGenSources(1,&IDSource);
    alBufferData(IDSound,sound.Format,sound.Buffer,sound.Size,sound.Frequency);
    if(!IDSource){
        alDeleteBuffers(1,&IDSound);
        return 0 ;
    }
    alSourcei(IDSource,AL_BUFFER,IDSound);
    if(!addID(IDSound,IDSource)){
        alDeleteSources(1,&IDSource);
        alDeleteBuffers(1,&IDSound);
        return 0 ;
    }
    return m_nbSounds;

};
void SoundEngine::PlaySound(ALuint ID,Actor* Source){
    if(ID <= m_nbSounds && ID > 0){
        alSourceStop(v_Sources[ID]);
        if(Source){
            Vertex3d ver =Source->getPosition();
            alSource3f(v_Sources[ID],AL_POSITION,ver.x,ver.y,ver.z);
        }else{
            alSource3f(v_Sources[ID],AL_POSITION,0.0f,0.0f,0.0f);
        }
        alSourcePlay(v_Sources[ID]);
    }
};
bool SoundEngine::LoadMusic(Sound* Music ,bool Repeat){
    if(!m_MusicSource){
        alGenSources(1,&m_MusicSource);
        if(!m_MusicSource)
            return false ;
    }
    alSourceStop(m_MusicSource);
    m_MusicStatus=SSTOP;
    if(Music){
        if(m_MusicBuffer){
            alDeleteBuffers(1,&m_MusicBuffer);
            m_MusicBuffer=0 ;
        }
        alGenBuffers(1,&m_MusicBuffer);
        if(!m_MusicBuffer)
            return false ;

        alBufferData(m_MusicBuffer,Music->Format,Music->Buffer,Music->Size,Music->Frequency);
        alSourcei(m_MusicSource,AL_BUFFER,m_MusicBuffer);
    }
    else
        alSourcei(m_MusicSource,AL_BUFFER,0);
    this->setRepeatMusic(Repeat);
    return true ;
};
void SoundEngine::setRepeatMusic(bool Repeat){
    if(m_MusicSource){
        alSourcei(m_MusicSource,AL_LOOPING,(Repeat?AL_TRUE:AL_FALSE));
        m_Repeat=Repeat;
    }
};
bool SoundEngine::isRepeating (){
    return m_Repeat;
};
void SoundEngine::PlayMusic(){
    if(m_MusicSource)
    if(m_MusicStatus !=SPLAY){
        alSourcePlay(m_MusicSource);
        m_MusicStatus=SPLAY;
    }
};
void SoundEngine::PauseMusic(){
    if(m_MusicSource)
    if(m_MusicStatus !=SPAUSE){
        alSourcePause(m_MusicSource);
        m_MusicStatus=SPAUSE;
    }
};
void SoundEngine::StopMusic(){
    if(m_MusicSource)
    if(m_MusicStatus !=SSTOP){
        alSourceStop(m_MusicSource);
        m_MusicStatus=SSTOP;
    }
};
bool SoundEngine::isPlaying(){
    if(!m_MusicSource)
        return false;
    if(m_MusicStatus==SPLAY)
        return true ;
    return false ;
    /*ALint tmp ;
    alGetSourcei(m_MusicSource,AL_PLAYING,&tmp);
    if(tmp)
        return true;
    else
        return false ;*/
};
bool SoundEngine::isPaused(){
    if(!m_MusicSource)
        return false;
    if(m_MusicStatus==SPAUSE)
        return true ;
    return false ;
};
bool SoundEngine::isStopped(){
    if(!m_MusicSource)
        return false;
    if(m_MusicStatus==SSTOP)
        return true ;
    return false ;
};
void SoundEngine::ReleaseBuffers(){
    if(v_Sounds){
        for(int i=0; i<m_nbSounds;i++){
            alDeleteBuffers(1,&(v_Sounds[i]));
            alDeleteSources(1,&(v_Sources[i]));
        }
        free(v_Sounds);
        free(v_Sources);
        v_Sources=NULL ;
        v_Sounds=NULL ;
        m_nbSounds=0;
    }
};
bool SoundEngine::addID(ALuint IDSound,ALuint IDSource){
    ALuint* tmp1=(ALuint*)malloc((m_nbSounds+1)*sizeof(ALuint));//for sounds
    ALuint* tmp2=(ALuint*)malloc((m_nbSounds+1)*sizeof(ALuint));
    if(!tmp2 && !tmp2)
        return false ;
    if(v_Sounds){
        for(int i=0 ; i < m_nbSounds;i++){
            tmp1[i]=v_Sounds[i];
            tmp2[i]=v_Sources[i];}
        free(v_Sounds);
        free(v_Sources);
    }
    tmp1[m_nbSounds]=IDSound ;
    tmp2[m_nbSounds]=IDSource;
    v_Sounds=tmp1;
    v_Sources=tmp2;
    m_nbSounds++ ;
    return true ;

};
Sound* SoundEngine::LoadWAVFile(char* filename){
Sound* Output=NULL ;
    FILE* soundFile = NULL;
    WAVE_Format wave_format;
    RIFF_Header riff_header;
    WAVE_Data wave_data;

    soundFile = fopen(filename, "rb");
    if (!soundFile){
        //printf("File not found\n");
        return NULL ;
    }

    // Read in the first chunk into the struct
    fread(&riff_header, sizeof(RIFF_Header), 1, soundFile);

    //check for RIFF and WAVE tag in memeory
    if ((riff_header.chunkID[0] != 'R' ||
         riff_header.chunkID[1] != 'I' ||
         riff_header.chunkID[2] != 'F' ||
         riff_header.chunkID[3] != 'F') ||
        (riff_header.format[0] != 'W' ||
         riff_header.format[1] != 'A' ||
         riff_header.format[2] != 'V' ||
         riff_header.format[3] != 'E')){
             fclose(soundFile);
             //printf("Not RIFF//WAVE format \n");
             return NULL ;
         }

    //Read in the 2nd chunk for the wave info
    fread(&wave_format, sizeof(WAVE_Format), 1, soundFile);
    //check for fmt tag in memory
    if (wave_format.subChunkID[0] != 'f' ||
        wave_format.subChunkID[1] != 'm' ||
        wave_format.subChunkID[2] != 't' ||
        wave_format.subChunkID[3] != ' '){
             fclose(soundFile);
             return NULL ;
         }

    //check for extra parameters;
    if (wave_format.subChunkSize > 16)
        fseek(soundFile, sizeof(short), SEEK_CUR);

    //Read in the the last byte of data before the sound file
    fread(&wave_data, sizeof(WAVE_Data), 1, soundFile);
    //check for data tag in memory
    if (wave_data.subChunkID[0] != 'd' ||
        wave_data.subChunkID[1] != 'a' ||
        wave_data.subChunkID[2] != 't' ||
        wave_data.subChunkID[3] != 'a'){
             fclose(soundFile);
             return NULL ;
         }

    //Allocate memory for output data
    if(!(Output=(Sound*)malloc(sizeof(Sound)))){
             fclose(soundFile);
             return NULL ;
         }

    Output->Size= wave_data.subChunk2Size;
    Output->Frequency = wave_format.sampleRate;
    //The format is worked out by looking at the number of
    //channels and the bits per sample.
    if (wave_format.numChannels == 1) {
        if (wave_format.bitsPerSample == 8 )
            Output->Format = AL_FORMAT_MONO8;
        else if (wave_format.bitsPerSample == 16)
            Output->Format = AL_FORMAT_MONO16;
    } else if (wave_format.numChannels == 2) {
        if (wave_format.bitsPerSample == 8 )
            Output->Format = AL_FORMAT_STEREO8;
        else if (wave_format.bitsPerSample == 16)
            Output->Format = AL_FORMAT_STEREO16;
    }

    //allocating buffer
    if(!(Output->Buffer =(unsigned char*)malloc(Output->Size))){
            free(Output);
             fclose(soundFile);
             return NULL ;
         }

    // Read in the sound data into the soundData variable
    if (!fread(Output->Buffer, wave_data.subChunk2Size, 1, soundFile)){
             free(Output->Buffer);
             free(Output);
             fclose(soundFile);
             return NULL ;
    }
    //clean up and return true if successful
    fclose(soundFile);
   return Output;
};
