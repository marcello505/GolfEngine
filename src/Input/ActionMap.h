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
    class ActionMap {
    private:
        std::map<std::string, Action> _actions;
        std::map<InputKey, std::vector<Action>> _inputKeys;
        Vector2 mousePosition;

        static ActionMap* actionMap;

    public:
        /// This method is used to get access to the action map instance
        /// \return Returns the global action map instance
        static ActionMap *getActionMap();

        void update();

        void addAction(const std::string &name);

        void addInputKeyToAction(const std::string &action, InputKey inputKey);

        bool isJustPressed(const std::string &action) const;

        bool isJustReleased(const std::string &action) const;

        bool isPressed(const std::string &action) const;

        bool isReleased(const std::string &action) const;

        Vector2 getMousePosition() const;

        void setMousePosition(int x, int y);

        ActionMap();

        void setInputKeyPressed(InputKey inputKey, bool pressed);
    };
#endif //GOLFENGINE_ACTIONMAP_H
