#define ACTIONMAP_PRIVATE
#include "ActionMap.h"
#include <iostream>

ActionMap::ActionMap()
{
    for (int fooInt = Key_0; fooInt != Key_Underscore; fooInt++)
    {
        _inputKeys.insert(std::pair<InputKey,
                std::vector<Action>>(static_cast<InputKey>(fooInt), std::vector<Action>()));
    }
}

void ActionMap::addAction(const std::string& name) {
    if (_actions.find(name) == _actions.end())
    {
        Action action;
        action.name = name;
        action.justInput = false;
        action.pressed = false;
        _actions.insert(std::pair<std::string, Action>(name, action));
    }
}

void ActionMap::addInputKeyToAction(const std::string& action, InputKey inputKey)
{
    if (_inputKeys.find(inputKey) != _inputKeys.end() && _actions.find(action) != _actions.end()) // if key and action exist
    {
        _inputKeys.find(inputKey)->second.push_back(_actions.find(action)->second);
    }
}

bool ActionMap::isJustPressed(const std::string& action) const
{

    if (_actions.find(action) != _actions.end() && _actions.find(action)->second.justInput)
    {
        std::cout << "Just pressed " << _actions.find(action)->second.name << "\n";
        return true;
    }

    return false;
}

bool ActionMap::isJustReleased(const std::string& action) const
{
    return false; // ??
}

bool ActionMap::isPressed(const std::string& action) const
{

    if (_actions.find(action) != _actions.end() && _actions.find(action)->second.pressed)
    {
        std::cout << "Pressed " << _actions.find(action)->second.name << "\n";
        return true;
    }

    return false;
}

bool ActionMap::isReleased(const std::string& action) const
{
    if (_actions.find(action) != _actions.end() && !_actions.find(action)->second.pressed)
    {
        std::cout << "Released " << _actions.find(action)->second.name << "\n";
        return true;
    }

    return false;
}

Vector2 ActionMap::getMousePosition() const
{
    return Vector2();
}

void ActionMap::setMousePosition()
{

}

void ActionMap::setInputKeyPressed(InputKey inputKey, bool pressed)
{
    if (!(_inputKeys.find(inputKey)->second.empty()))
    {
        if (pressed) {
            for (auto action : _inputKeys.find(inputKey)->second)
            {
                if (!_actions.find(action.name)->second.pressed)
                {
                    _actions.find(action.name)->second.justInput = true;
                    isJustPressed(action.name);
                }
                _actions.find(action.name)->second.pressed = true;
                isPressed(action.name);
            }
            return;
        }
        for (auto action : _inputKeys.find(inputKey)->second)
        {
            _actions.find(action.name)->second.pressed = false;
            isReleased(action.name);
        }
        return;
    }
}

void ActionMap::update()
{
    for (auto& action : _actions)
    {
        action.second.justInput = false;
    }
}

