#include "GameCore.h"

#ifdef main
#undef main
#endif // main

int main(int argc,char** argv){
    GameCore* Game=NULL ;
    Game=new GameCore();
    if(!Game->Init("Solo Striker Fantasy ver 1.00",800,600))
        return 1 ;
    Game->StartGame();
    Game->Destroy();
    delete Game ;
    return 0 ;
}
