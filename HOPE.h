#ifndef PFE_HOPE_H_
#define PFE_HOPE_H_
#include "Player.h"
#include "PlayerStatus.h"
#include "WeaponTypes.h"
#include "Math.h"
#include "CreditHandler.h"


class HOPE;
class Shooter:public DynamicModel {
public :
    Shooter(HOPE* Owner,Vertex3d Trans);
    ~Shooter();
    int LoadFromFile();
    void Update(float dt);
    int Fire(float dt,GameScene* Scene);
    void SelectWeapon(int index);
    int getSelectedWeapon();
    Weapon* getSelectedWeaponObj();
    void setTransVertex(Vertex3d ver);
    void Destroy();

private:
    HOPE*               m_Owner;
    Vertex3d            m_Trans ;
    Vertex3d            m_TmpVertex ;
    int                 m_nbWeapons;
    int                 m_SelectedWeapon;
    Weapon**            v_Weapons;
    ALuint              m_SwitchSound ;

};
class HOPE :public Player{
public :
    //Constructor
    HOPE();
    //Deconstructor
    ~HOPE();
    int LoadFromFile() ;//load HOPE model from a Known file
    void Destroy();
    void Init();
    void Draw(float* ViewMtx);
    void Update(float dt);//updates HOPE movement
    //void Update(SDL_Event event);//Update HOPE's Stat
    void Update(SDL_Event* Events, int nbEvents) ;
    void NextWeapon();
    void PreviousWeapon();
    void getDamage();
private :
    void Fire(float dt);
    float               m_Speed ;//HOPE movement speed
    Vertex3d            m_MoveDirection;
    Shooter*            m_Shooter1;
    Shooter*            m_Shooter2;
    PlayerStatus*       m_GStatus;
    CreditHandler*      m_CreditHandler;
    StaticModel*        m_GameOver;
    bool                m_Firing ;
};
#endif // PFE_HOPE_H_
