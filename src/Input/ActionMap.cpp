//
// Created by olafv on 11/2/2022.
//

#include "ActionMap.h"

void ActionMap::addAction(std::string name){};
void ActionMap::addInputKeyToAction(std::string action, InputKey inputKey){};
bool ActionMap::isJustPressed(std::string action){return false;};
bool ActionMap::isJustReleased(std::string action){return false;};
bool ActionMap::isPressed(std::string action){return false;};
bool ActionMap::isReleased(std::string action){return false;};