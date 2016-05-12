#ifndef PFE_HOPE_H_
#define PFE_HOPE_H_
#include "Player.h"
#include "WeaponTypes.h"
#include "Math.h"
class HOPE;
class Shooter:public DynamicModel {
public :
    Shooter(HOPE* Owner,Vertex3d Trans);
    ~Shooter();
    int LoadFromFile();
    void Update(float dt);
    int Fire(float dt,GameScene* Scene);
    void SelectWeapon(int index);
    void setTransVertex(Vertex3d ver);
    void Destroy();
private:
    HOPE*               m_Owner;
    Vertex3d            m_Trans ;
    int                 m_nbWeapons;
    int                 m_SelectedWeapon;
    Weapon**            v_Weapons;

};

class HOPE :public Player{
public :
    //Constructor
    HOPE();
    //Deconstructor
    ~HOPE();
    int LoadFromFile() ;//load HOPE model from a Known file
    void Destroy();
    void Draw(float* ViewMtx);
    void Update(float dt);//updates HOPE movement
    //void Update(SDL_Event event);//Update HOPE's Stat
    void Update(SDL_Event* Events, int nbEvents) ;
private :
    void Fire(float dt);
    float               m_Speed ;//HOPE movement speed
    Vertex3d            m_MoveDirection;
    Shooter*            m_Shooterl;
    Shooter*            m_Shooter2;
    bool                m_Firing ;
};
#endif // PFE_HOPE_H_
