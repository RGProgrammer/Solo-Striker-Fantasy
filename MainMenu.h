#ifndef PFE_MAINMENU_H_
#define PFE_MAINMENU_H_
#include "Player.h"

enum SELECTEDITEM {
    STARTGAME  = 0 ,
    SCORE      = 1 ,
    EXIT       = 2
};

class MainMenu: public Player {
public:
    MainMenu();
    ~MainMenu();
    int LoadFromFile();
    void Init();
    void Update(float dt);
    void Update(SDL_Event* Events, int nbEvents) ;
    int getSelectedItem();
    void Draw(float* viewMtx);
    void Destroy();
private :
    StaticModel**       v_SubItems ;
    StaticModel*        m_Selector ;
    int                 m_nbItems;
    int                 m_Selected;

};
#endif // PFE_MAINMENU_H_
