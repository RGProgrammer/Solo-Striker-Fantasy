#ifndef PFE_GLOBALSOUND_H_
#define PFE_GLOBALSOUND_H_
#include "SoundEngine.h"

static SoundEngine* GlobalSoundHandler=NULL ;
 SoundEngine* getGlobalSoundEngineInstance();
 int CreateGlobalSoundEngine();//create and Initialize GlobalSoundEngine
 void DestroyGlobalSoundEngine();

#endif // PFE_GLOBALSOUND_H_
