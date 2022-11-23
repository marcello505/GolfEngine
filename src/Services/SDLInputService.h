
#ifndef SPC_PROJECT_SDLINPUTSERVICE_H
#define SPC_PROJECT_SDLINPUTSERVICE_H

#include "Abstracts/InputService.h"
#include "../Input/ActionMap.h"
#include "../Input/InputKey.h"
#include <SDL.h>

class SDLInputService : public InputService {
private:
    ActionMap* _actionMap;
    std::map<std::string, InputKey> _inputBinds;
    void bindKeys();
    void handleMouseEvent(SDL_Event event, bool pressed);
    bool _hasRecievedQuitSignal {};
public:
    SDLInputService();
    void handleInputs() override;

    bool hasRecievedQuitSignal() override;

};


#endif //SPC_PROJECT_SDLINPUTSERVICE_H