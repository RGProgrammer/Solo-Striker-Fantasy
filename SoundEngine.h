#ifndef PFE_SOUNDENGINE_H_
#define PFE_SOUNDENGINE_H_
#include "Actor.h"
#include ".//tools//Openal//al.h"
#include ".//tools//Openal//alc.h"
#include <stdlib.h>
#include <stdio.h>

#define SSTOP        0
#define SPAUSE       1
#define SPLAY        2
typedef struct {
    ALenum Format ;
    ALsizei Frequency;
    ALsizei Size;
    unsigned char* Buffer;
} Sound ;

struct RIFF_Header {
  char chunkID[4];
  long chunkSize;//size not including chunkSize or chunkID
  char format[4];
};

struct WAVE_Data {
  char subChunkID[4]; //should contain the word data
  long subChunk2Size; //Stores the size of the data block
};

struct WAVE_Format {
  char subChunkID[4];
  long subChunkSize;
  short audioFormat;
  short numChannels;
  long sampleRate;
  long byteRate;
  short blockAlign;
  short bitsPerSample;
};

class SoundEngine {
public:
    SoundEngine();
    ~SoundEngine();
    int InitEngine();
    void Destroy();
    void setListener(Actor* Listener);
    ALuint LoadSound(Sound sound,Actor* Source);
    void PlaySound(ALuint ID);
    bool LoadMusic(Sound* Music ,bool repeat=false);
    void setRepeatMusic(bool Repeat);
    bool isRepeating ();
    void PlayMusic();
    void PauseMusic();
    void StopMusic();
    bool isPlaying();
    bool isPaused();
    bool isStopped();
    void ReleaseBuffers();//release only the sound buffers and not the music
public:
    static Sound* LoadWAVFile(char* filename);
private:
    ALCdevice*              m_Device ;
    ALCcontext*             m_Context;
    ALuint                  m_MusicBuffer ;
    ALuint                  m_MusicSource;// initialized via set Listener;
    int                     m_MusicStatus ;
    bool                    m_Repeat ;
};
#endif // PFE_SOUNDENGINE_H_
