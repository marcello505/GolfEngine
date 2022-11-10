
#ifndef SPC_PROJECT_SDLINPUTSERVICE_H
#define SPC_PROJECT_SDLINPUTSERVICE_H

#include "Abstracts/InputService.h"
#include "../Input/ActionMap.h"
#include "../Input/InputKey.h"

class SDLInputService {
private:
    ActionMap* _actionMap;
    std::map<std::string, InputKey> _inputBinds;
    void bindKeys();
public:
    SDLInputService(ActionMap* actionMap);
    void handleInputs();
};


#endif //SPC_PROJECT_SDLINPUTSERVICE_H
