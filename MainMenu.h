#ifndef PFE_MAINMENU_H_
#define PFE_MAINMENU_H_
#include "Player.h"
class MainMenu{
public:
    MainMenu()
    ~MainMenu()
    int LoadFromFile();
    void Update(float dt);
    void Update(SDL_Event event);
private :
    StaticModel**       v_SubItems ;
    int                 m_nbItems;
    int                 m_Selected;

};
#endif // PFE_MAINMENU_H_
