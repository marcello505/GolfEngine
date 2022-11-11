#define ACTIONMAP_PRIVATE
#include "ActionMap.h"
#include <iostream>
ActionMap::ActionMap()
{
    for (int fooInt = Key_0; fooInt != Mouse_Right + 1; fooInt++)
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


    if (_inputKeys.count(inputKey) > 0 && _actions.find(action) != _actions.end()) // if key and action exist
    {
        _inputKeys.find(inputKey)->second.push_back(_actions.find(action)->second);
    }
}

bool ActionMap::isJustPressed(const std::string& action) const
{

    if (_actions.find(action) != _actions.end() && _actions.find(action)->second.justInput)
    {
/*        throw "Just pressed " + _actions.find(action)->second.name;*/
        std::cout << "Just pressed " << _actions.find(action)->second.name << std::endl;;
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
        std::cout << "Pressed " << _actions.find(action)->second.name << std::endl;;
        return true;
    }

    return false;
}

bool ActionMap::isReleased(const std::string& action) const
{
    if (_actions.find(action) != _actions.end() && !_actions.find(action)->second.pressed)
    {
        std::cout << "Released " << _actions.find(action)->second.name << std::endl;
        return true;
    }

    return false;
}

Vector2 ActionMap::getMousePosition() const
{
    std::cout << "Mouse cursor is at " << mousePosition.x << ", " << mousePosition.y << std::endl;
    return mousePosition;
}

void ActionMap::setMousePosition(int x, int y)
{
    Vector2 vector{};
    vector.x = (float)x;
    vector.y = (float)y;

    mousePosition = vector;
}

void ActionMap::setInputKeyPressed(InputKey inputKey, bool pressed)
{
    auto key = _inputKeys.find(inputKey);
    if (!(key->second.empty()))
    {
        if (pressed) {
            for (const auto& action : _inputKeys.find(inputKey)->second)
            {
                if (!_actions.find(action.name)->second.pressed)
                {
                    _actions.find(action.name)->second.justInput = true;
                    isJustPressed(action.name);
                    isPressed(action.name);
                }
                _actions.find(action.name)->second.pressed = true;
                isPressed(action.name);
            }
            return;
        }
        for (const auto& action : _inputKeys.find(inputKey)->second)
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

