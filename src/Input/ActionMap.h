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
    void addAction(string name);
    void addInputKeyToAction(string action, InputKey inputKey);
    bool isJustPressed(string action);
    bool isJustReleased(string action);
    bool isPressed(string action);
    bool isReleased(string action);
    Vector2 getMousePosition();
};


#endif //GOLFENGINE_ACTIONMAP_H
