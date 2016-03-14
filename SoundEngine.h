#ifndef PFE_SOUNDENGINE_H_
#define PFE_SOUNDENGINE_H_
#include <stdio.h>
#include "Actor.h"
typedef struct {
    float length ;
    float frequency ;
    char* buffer ;
} Sound ;

class SoundEngine {
public:
    SoundEngine();
    ~SoundEngine();
    void PlaySound(Sound* sound ,Actor* source);
    void PlayMusic(Sound* Music,bool repeat);
    void Destroy();
    static Sound* LoadfromFile(char* filename);
private:
    Sound*                      m_Music;
    bool                        m_MusicRepeat;
    int                         m_nbSounds;
    Sound*                      v_Sounds ;
    Actor**                     v_Sources ;
    Actor*                      m_Listener ;

};
#endif // PFE_SOUNDENGINE_H_
