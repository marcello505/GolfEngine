
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
    bool _hasReceivedQuitSignal {};
    bool _pressedKey {};
public:
    SDLInputService();

    // Input Service overrides
    void handleInputs() override;
    InputKey getKeyPressed() override;
    [[nodiscard]] bool hasReceivedQuitSignal() const override;
    [[nodiscard]] bool pressedKey() const override;
    void setKeyPressed(bool pressed) override;
    std::string getKeyString(InputKey key) override;
};


#endif //SPC_PROJECT_SDLINPUTSERVICE_H