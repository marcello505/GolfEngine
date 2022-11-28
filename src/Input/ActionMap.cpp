#define ACTIONMAP_PRIVATE
#include "ActionMap.h"
#include <iostream>

// constructor
ActionMap::ActionMap()
{
    // add key values to inputkeys list
    for (int fooInt = Key_0; fooInt != Mouse_Right + 1; fooInt++)
    {
        _inputKeys.insert(std::pair<InputKey,
                std::vector<Action>>(static_cast<InputKey>(fooInt), std::vector<Action>()));
    }
}

// add action to actionlist
void ActionMap::addAction(const std::string& name) {
    if (_actions.count(name) <= 0)
    {
        Action action;
        action.name = name;
        action.justInput = false;
        action.pressed = false;
        _actions.insert(std::pair<std::string, Action>(name, action));
    }
}

// bind action to input
void ActionMap::addInputKeyToAction(const std::string& action, InputKey inputKey)
{
    if (_inputKeys.count(inputKey) > 0 && _actions.find(action) != _actions.end()) // if key and action exist
    {
        _inputKeys.find(inputKey)->second.push_back(_actions.find(action)->second);
    }
}

// check if action is just pressed (important for gameloop)
bool ActionMap::isJustPressed(const std::string& action) const
{

    if (_actions.count(action) > 0 && _actions.find(action)->second.justInput)
    {
/*        throw "Just pressed " + _actions.find(action)->second.name;*/
        std::cout << "Just pressed " << _actions.find(action)->second.name << std::endl;;
        return true;
    }

    return false;
}

// check if action is just released (important for gameloop)
bool ActionMap::isJustReleased(const std::string& action) const
{
    if (_actions.count(action) > 0  && _actions.find(action)->second.justInput
    && !(_actions.find(action)->second.pressed)) {
        return true;
    }
    return false;
}

// check if action is pressed
bool ActionMap::isPressed(const std::string& action) const
{

    if (_actions.count(action) > 0  && _actions.find(action)->second.pressed)
    {
        std::cout << "Pressed " << _actions.find(action)->second.name << std::endl;;
        return true;
    }

    return false;
}

// check if action is released
bool ActionMap::isReleased(const std::string& action) const
{
    if (_actions.count(action) > 0  && !_actions.find(action)->second.pressed)
    {
        std::cout << "Released " << _actions.find(action)->second.name << std::endl;
        return true;
    }

    return false;
}

// get position of mouse
Vector2 ActionMap::getMousePosition() const
{
    return mousePosition;
}

// set position of the mouse
void ActionMap::setMousePosition(int x, int y)
{
    Vector2 vector{};
    vector.x = (float)x;
    vector.y = (float)y;

    mousePosition = vector;
}

// setting variables (pressed, justPressed) of actions (called from inputservice)
void ActionMap::setInputKeyPressed(InputKey inputKey, bool pressed)
{
    if (!(_inputKeys.find(inputKey)->second.empty())) // if key has any actions bind to it
    {
        if (pressed) { // if we press
            for (const auto& action : _inputKeys.find(inputKey)->second)
            {
                if (!_actions.find(action.name)->second.pressed) // set justInput to true if wasnt pressed already
                {
                    _actions.find(action.name)->second.justInput = true;
                    isJustPressed(action.name);
                    isPressed(action.name);
                }
                _actions.find(action.name)->second.pressed = true; // set pressed to true
                isPressed(action.name);
            }
            return;
        }
        for (const auto& action : _inputKeys.find(inputKey)->second) // if we release
        {
            _actions.find(action.name)->second.pressed = false; // set pressed to false (released)
            isReleased(action.name);
        }
        return;
    }
}

// set default value of justinput on gametick
void ActionMap::update()
{
    for (auto& action : _actions)
    {
        action.second.justInput = false;
    }
}

