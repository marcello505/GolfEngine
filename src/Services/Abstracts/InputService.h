//
// Created by conner on 11/2/2022.
//

#ifndef SPC_PROJECT_INPUTSERVICE_H
#define SPC_PROJECT_INPUTSERVICE_H

#include "Input/InputKey.h"
#include <string>

class InputService {
public:
    virtual void handleInputs() = 0;
    virtual bool hasReceivedQuitSignal() const = 0;
    virtual bool pressedKey() const = 0;
    virtual void setKeyPressed(bool pressed) = 0;
    virtual InputKey getKeyPressed() = 0;
    virtual std::string getKeyString(InputKey key) = 0;
};


#endif //SPC_PROJECT_INPUTSERVICE_H
