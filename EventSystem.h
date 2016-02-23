#ifndef PFE_EVENTSYSTEM_H_
#define PFE_EVENTSYSTEM_H_
#include ".//tools//sdl2//include//SDL.h"
#include <stdlib.h>
class EventSystem{
public:
    EventSystem();
    ~EventSystem();
    SDL_Event getSDLEvent();
private:
    SDL_Joystick*       m_Joystick ;
    SDL_Event           m_Event;
};
#endif // PFE_EVENTSYSTEM_H_
