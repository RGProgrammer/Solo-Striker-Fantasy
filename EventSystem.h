#include ".//tools//sdl2//include//SDL.h"
#define NOSOURCE       0x0000
#define JOYSTICK       0x0001
#define KEYBOARD       0x0002
#define MOUSE          0x0004
typedef struct {

} Event ;
class EventSystem{
public:
    EventSystem();
    ~EventSystem();
    Event getNextEvent();
    SDL_Event getSDLEvent();
private:
    int                 SourceType ;
    SDL_Joystick*       m_Joystick ;
    SDL_Event           m_Event;
};
