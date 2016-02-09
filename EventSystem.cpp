#include "EventSystem.h"

EventSystem::EventSystem():m_Joystick(NULL),SourceType(NOSOURCE){
};
EventSystem::~EventSystem(){
};
Event EventSystem::getNextEvent(){

};
SDL_Event EventSystem::getSDLEvent(){
    SDL_PollEvent(&m_Event);
    return m_Event ;
};
