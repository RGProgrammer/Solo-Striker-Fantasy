#ifndef PFE_HOPE_H_
#define PFE_HOPE_H_
#include "Player.h"
#include "WeaponTypes.h"

class HOPE :public Player{
public :
    //Constructor
    HOPE();
    //Deconstructor
    ~HOPE();
    int LoadFromFile() ;//load HOPE model from a Known file
    void Update(float dt);//updates HOPE movement
    //void Update(SDL_Event event);//Update HOPE's Stat
    void Update(SDL_Event* Events, int nbEvents) ;
private :
    void Fire();
    float               m_Speed ;//HOPE movement speed
    int                 m_nbWeapons;
    int                 m_SelectedWeapon;
    Weapon**            v_Weapons;
    Vertex3d            m_MoveDirection;

};
#endif // PFE_HOPE_H_
