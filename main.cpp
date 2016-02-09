#include "GameCore.h"

#ifdef main
#undef main
#endif // main

int main(int argc,char** argv){
    GameCore* Core=NULL ;
    Core=new GameCore();
    if(!Core->Init("Solo Striker Fantasy ver 1.00",800,600))
        return 1 ;
    Core->StartGame();
    Core->Destroy();
    delete Core ;
    return 0 ;
}
