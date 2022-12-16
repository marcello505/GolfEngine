
#ifndef SPC_PROJECT_SDLINPUTSERVICE_H
#define SPC_PROJECT_SDLINPUTSERVICE_H

#include "Abstracts/InputService.h"
#include "../Input/ActionMap.h"
#include "../Input/InputKey.h"

// Forward declaration
class Event_Wrapper;

class SDLInputService : public InputService {
private:
    ActionMap* _actionMap;
    std::map<std::string, InputKey> _inputBinds;
    void bindKeys();
    void handleMouseEvent(Event_Wrapper event, bool pressed);
    bool _hasReceivedQuitSignal {};
public:
    SDLInputService();
    void handleInputs() override;

    [[nodiscard]] bool hasReceivedQuitSignal() const override;

};


#endif //SPC_PROJECT_SDLINPUTSERVICE_H