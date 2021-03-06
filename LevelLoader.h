#ifndef PFE_LEVELLOADER_H_
#define PFE_LEVELLOADER_H_
#include "GameScene.h"
#include "UFO.h"
#include "AEX2.h"
#include "Blades.h"
#include "Canon.h"
#include "FIRST.h"
#include "ShotTypes.h"
#include "Terrain.h"
#include "util.h"
#include "GlobalSound.h"
#include <stdlib.h>
class LevelLoader {
public:
static int LoadLevel(char* filename,GameScene * Scene);
    LevelLoader();
    ~LevelLoader();
    int LoadLevelFile(char* filename,GameScene* Scene);
private:
    int DecodeActionLine(char* line);
    int DecodeEnemyLine(char* line);
    int DecodeBossLine(char* line);
    int DecodeTerrainLine(char* line);
    int DecodeSkyboxLine(char* line);
    int DecodeCameraLine(char* line );
    int DecodeMusicLine(char* line);
    GameScene*           m_Scene;
    Enemy*               m_Sample;
};
#endif // PFE_LEVELLOADER_H_
