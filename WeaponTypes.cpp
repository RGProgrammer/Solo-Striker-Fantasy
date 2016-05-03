#include "WeaponTypes.h"

MachineGun::MachineGun(Actor* Owner):Weapon("machinegun",Owner,NULL){
    m_Sample= new EnergyBullet(Owner);
    m_Sample->LoadFromFile();
};
MachineGun::~MachineGun(){
};
int MachineGun::Fire(GameScene* Scene,Vertex3d Pos,Vertex3d Dir,Vertex3d Up){
    //if(m_Dt>= m_TimeBetweenShots){
        Shot * bullet=NULL ;
        bullet=m_Sample->Clone();
        if(!bullet)
            return 0 ;
        //m_Dt=0;
        bullet->setPosition(Pos);
        bullet->setOrientation(Dir,Up);
        bullet->setSource(m_Owner);
        return Scene->AddActor(bullet);
    //}
};




