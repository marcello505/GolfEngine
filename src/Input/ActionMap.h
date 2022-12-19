//
// Created by olafv on 11/2/2022.
//

#ifndef GOLFENGINE_ACTIONMAP_H
#define GOLFENGINE_ACTIONMAP_H

#include <map>
#include <string>
#include <vector>
#include <memory>
#include "Action.h"
#include "InputKey.h"
#include "../Scene/Vector2.h"

using namespace GolfEngine::Scene;

namespace GolfEngine::Input {
    class ActionMap {
    private:
        std::map<std::string, Action> _actions;
        std::map<InputKey, std::vector<Action>> _inputKeys;
        Vector2 mousePosition;

        static ActionMap *actionMap;

    public:
        ActionMap();

        /// This method is used to get access to the action map instance
        /// \return Returns the global action map instance
        static ActionMap *getActionMap();

        /// Resets the just pressed actions
        void update();

        /// Adds and action to the action map
        /// \param name Name of the action to later reference
        void addAction(const std::string &name);

        /// Adds an input key to an action
        /// \param action The action to link the key to
        /// \param inputKey Key to be linked to the action
        void addInputKeyToAction(const std::string &action, InputKey inputKey);

        /// Checks whether a key has just been pressed, will only be 1 frame
        /// \param action to be checked
        /// \return true if key has just been pressed
        [[nodiscard]] bool isJustPressed(const std::string &action) const;

        /// Checks whether a key has just been released, will only be 1 frame
        /// \param action to be checked
        /// \return true if key has just been released
        [[nodiscard]] bool isJustReleased(const std::string &action) const;

        /// Checks whether a key is being pressed
        /// \param action to be checked
        /// \return true if key is currently being pressed
        [[nodiscard]] bool isPressed(const std::string &action) const;

        /// Checks whether a key is not being pressed
        /// \param action to be checked
        /// \return true if key is currently not being pressed
        [[nodiscard]] bool isReleased(const std::string &action) const;

        /// Retrieves the current position of the mouse
        /// \return Position of mouse in a vector2
        [[nodiscard]] Vector2 getMousePosition() const;

        /// Override mouse position
        /// \param x position
        /// \param y position
        void setMousePosition(int x, int y);

        /// Override a key press with a state (pressed/released)
        /// \param inputKey key to override
        /// \param pressed state of key press
        void setInputKeyPressed(InputKey inputKey, bool pressed);

        /// Gets all input keys linked to an action
        /// \param action to get all keys from
        /// \return A list of all the keys linked to the action
        std::vector<InputKey> getActionKeys(std::string action);

        /// Remove all input keys linked to an action
        /// \param action to remove the links from
        void removeInputKeysFromAction(std::string &action);

        /// Primarily used by Replays to directly set the inputs
        /// \param action name of the action
        /// \param pressed value to set action.pressed to
        /// \param justInput value to set action.justInput to
        void setActionPressed(const std::string &action, bool pressed, bool justInput);
    };
}

#endif //GOLFENGINE_ACTIONMAP_H
