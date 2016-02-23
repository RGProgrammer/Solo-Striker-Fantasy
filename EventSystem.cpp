#include "EventSystem.h"
EventSystem::EventSystem():m_Joystick(NULL) {
};
EventSystem::~EventSystem(){
    if(m_Joystick)
        free(m_Joystick);
};

SDL_Event EventSystem::getSDLEvent(){
    SDL_PollEvent(&m_Event);
    return m_Event ;
};
