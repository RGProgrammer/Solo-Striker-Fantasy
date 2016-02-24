#include "WeaponTypes.h"

MachineGun::MachineGun(Actor* Owner):Weapon("machinegun",Owner,NULL){
    m_Sample= new EnergyBullet(Owner);
    m_Sample->LoadFromFile();
};
MachineGun::~MachineGun(){
};
int MachineGun::Fire(GameScene* Scene,Vertex3d Pos,Vertex3d Dir,Vertex3d Up){
    //if(m_Dt>= m_TimeBetweenShots){
        Shot * bullet=new EnergyBullet(Pos,Dir,Up);
        if(!bullet->Clone(m_Sample)){
            delete bullet;
            return 0 ;
        }
        //m_Dt=0;
        return Scene->AddActor((StaticModel*)bullet);
    //}
    return 1 ;
};

ChaserLauncher::ChaserLauncher():Weapon("chaserlauncher",NULL,NULL){
};
ChaserLauncher::~ChaserLauncher(){
};



