//
// Created by conner on 11/2/2022.
//

#ifndef SPC_PROJECT_INPUTSERVICE_H
#define SPC_PROJECT_INPUTSERVICE_H

#include "Input/InputKey.h"
#include <string>

using namespace GolfEngine::Input;

namespace GolfEngine::Services::Input {
    class InputService {
    public:
        /// Handles the inputs and updates the action map
        virtual void handleInputs() = 0;

        /// Has the window received a quit signal
        /// \return true if quit signal has been received
        [[nodiscard]] virtual bool hasReceivedQuitSignal() const = 0;

        /// Check for if any key has been pressed
        /// \return true if a key has been pressed
        [[nodiscard]] virtual bool pressedKey() const = 0;

        /// Reset if a key has been pressed
        /// \param pressed boolean for overriding keyPressed state
        virtual void setKeyPressed(bool pressed) = 0;

        /// Returns next raw key press
        /// \return Next raw key pressed
        virtual InputKey getKeyPressed() = 0;

        /// Coverts an InputKey enum to string format
        /// \param key to be converted
        /// \return string corresponding to the key input
        virtual std::string getKeyString(InputKey key) = 0;

        // Virtual Destructors
        virtual ~InputService() = default;
    };
}

#endif //SPC_PROJECT_INPUTSERVICE_H
