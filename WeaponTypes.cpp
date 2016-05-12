#include "WeaponTypes.h"

MachineGun::MachineGun(Actor* Owner):Weapon("machinegun",Owner,NULL){
    m_Sample= new EnergyBullet(Owner);
    m_Sample->LoadFromFile();
    Sound* effect=SoundEngine::LoadWAVFile("Sound//shoot.wav");
    if(effect){
        m_FireSound=getGlobalSoundEngineInstance()->LoadSound(*effect);
        free(effect->Buffer);
        free(effect);
    }
    m_TimeBetweenShots=0.10f;
};
MachineGun::~MachineGun(){
};
int MachineGun::Fire(float dt ,GameScene* Scene,Vertex3d Pos,Vertex3d Dir,Vertex3d Up){
    m_Dt+=dt;
    if(m_Dt>= m_TimeBetweenShots){
        Shot * bullet=NULL ;
        bullet=m_Sample->Clone();
        if(!bullet)
            return 0 ;
        m_Dt=0;
        bullet->setPosition(Pos);
        bullet->setOrientation(Dir,Up);
        bullet->setSource(m_Owner);
        getGlobalSoundEngineInstance()->PlaySound(m_FireSound,m_Owner);
        return Scene->AddActor(bullet);
    }
};




