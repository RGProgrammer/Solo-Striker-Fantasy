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
    void Update(SDL_Event* Events,int nbEvents);//Update HOPE's Stat
private :
    void NextWeapon();
    void PreviousWeapon();
    void Fire();
    float       m_Speed ;//HOPE movement speed

};
#endif // PFE_HOPE_H_
