//
// Created by olafv on 11/2/2022.
//

#ifndef GOLFENGINE_ACTIONMAP_H
#define GOLFENGINE_ACTIONMAP_H
#include <map>
#include <string>
#include <vector>
#include "Action.h"
#include "InputKey.h"
#include "Scene/Vector2.h"

class ActionMap {
private:
    std::map<std::string, Action> _actions;
    std::map<InputKey, std::vector<Action>> _inputKeys;
    void setInputKeyPressed(InputKey inputKey, bool pressed);
    void update();
    void setMousePosition();
public:
    void addAction(std::string name);
    void addInputKeyToAction(std::string action, InputKey inputKey);
    bool isJustPressed(std::string action);
    bool isJustReleased(std::string action);
    bool isPressed(std::string action);
    bool isReleased(std::string action);
    Vector2 getMousePosition();
};


#endif //GOLFENGINE_ACTIONMAP_H
