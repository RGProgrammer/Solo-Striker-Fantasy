#include "WeaponTypes.h"

MachineGun::MachineGun(Actor* Owner):Weapon("machinegun",Owner,NULL){
    m_Sample= new EnergyBullet(Owner);
    m_Sample->LoadFromFile();
    Sound* effect=SoundEngine::LoadWAVFile("Sound//shoot1.wav");
    if(effect){
        m_FireSound=getGlobalSoundEngineInstance()->LoadSound(*effect);
        free(effect->Buffer);
        free(effect);
    }
    m_Icon=new StaticModel();
    m_Icon->LoadFromFile("Data//MG_Icon.obj");
    m_TimeBetweenShots=0.10f;
};
MachineGun::~MachineGun(){
    this->Destroy() ;
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
    return 1;
};
Rampage::Rampage(Actor* Owner):Weapon("rampage",Owner,NULL),m_MaxRotation(0.78539816339f){
    m_Sample= new EnergyBullet(Owner);
    m_Sample->LoadFromFile();
    Sound* effect=SoundEngine::LoadWAVFile("Sound//shoot1.wav");
    if(effect){
        m_FireSound=getGlobalSoundEngineInstance()->LoadSound(*effect);
        free(effect->Buffer);
        free(effect);
    }
    m_Icon=new StaticModel();
    m_Icon->LoadFromFile("Data//RP_Icon.obj");
    m_TimeBetweenShots=0.10f;
};
Rampage::~Rampage(){
    this->Destroy() ;
};
int Rampage::Fire(float dt, GameScene* Scene,Vertex3d Pos,Vertex3d Dir,Vertex3d Up){
    ///this code is for test
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
    return 1;

};

EnemyChaserLauncher::EnemyChaserLauncher(Actor* Owner):Weapon("enemychaser",Owner,NULL),m_Target(NULL){
    m_Sample= new EnergyBullet(Owner);
    m_Sample->LoadFromFile();
    Sound* effect=SoundEngine::LoadWAVFile("Sound//shoot1.wav");
    if(effect){
        m_FireSound=getGlobalSoundEngineInstance()->LoadSound(*effect);
        free(effect->Buffer);
        free(effect);
    }
    m_Icon=new StaticModel();
    m_Icon->LoadFromFile("Data//EC_Icon.obj");
    m_TimeBetweenShots=0.10f;
};
EnemyChaserLauncher::~EnemyChaserLauncher(){
  this->Destroy() ;
};
int EnemyChaserLauncher::Fire(float dt,GameScene* Scene,Vertex3d Pos, Vertex3d Dir,Vertex3d Up){
    ///this code is for test
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
    return 1;
};


