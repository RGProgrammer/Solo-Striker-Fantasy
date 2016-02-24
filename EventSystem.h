#ifndef PFE_EVENTSYSTEM_H_
#define PFE_EVENTSYSTEM_H_
#include ".//tools//sdl2//include//SDL.h"
#include <stdlib.h>
class EventSystem{
public:
    EventSystem();
    ~EventSystem();
    SDL_Event getSDLEvent();
    SDL_Event* getCurrentFrameEvents();
    int getNbEvents();
private:
    SDL_Joystick*       m_Joystick ;
    SDL_Event*          v_Event;
    int                 m_nbEvents ;
};
#endif // PFE_EVENTSYSTEM_H_
