#include "EventSystem.h"
EventSystem::EventSystem():m_Joystick(NULL),v_Event(NULL),m_nbEvents(0) {
    v_Event=(SDL_Event*)malloc(5*sizeof(SDL_Event));
};
EventSystem::~EventSystem(){
    if(m_Joystick)
        free(m_Joystick);
    if(v_Event)
        free(v_Event);
};

/*SDL_Event EventSystem::getSDLEvent(){
    SDL_PollEvent(&m_Event);
    return m_Event ;
};*/
SDL_Event* EventSystem::getCurrentFrameEvents(){
   /* SDL_Event tmp;
    for(m_nbEvents=0 ;m_nbEvents <5 ;){
        if(SDL_PollEvent(&tmp)){
            v_Event[m_nbEvents]=tmp ;
            m_nbEvents++ ;
        }
    }*/
    for(m_nbEvents=0 ;m_nbEvents <5 && SDL_PollEvent(&v_Event[m_nbEvents]);m_nbEvents++);
    return v_Event;
};
int EventSystem::getNbEvents(){
    return m_nbEvents ;
};
