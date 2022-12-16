#define ACTIONMAP_PRIVATE


#include "ActionMap.h"
#include <iostream>
#include <algorithm>

ActionMap* ActionMap::actionMap = nullptr;


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
    // This method is used to get access to the scene manager instance
    /// \return Returns the global scene manager instance
    ActionMap* ActionMap::getActionMap(){
        if(actionMap == nullptr)
            actionMap = new ActionMap();
        return actionMap;
    }

    std::vector<InputKey> ActionMap::getActionKeys(std::string action){
        std::vector<InputKey> inputKeys;
        for (auto &_actionList : _inputKeys) {
            for (auto &_action: _actionList.second) {
                if (_action.name == action) {
                    inputKeys.push_back(_actionList.first);
                }
            }
        }

        return inputKeys;
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

    // remove action from actionlist
    void ActionMap::removeInputKeyFromAction(std::string& action){
        for (auto &_actionList : _inputKeys){
            for (auto &_action : _actionList.second){
                if(_action.name == action){
                    _actionList.second.erase(std::find_if(_actionList.second.begin(), _actionList.second.end(), [&](const Action &d) {
                        return &d == &_action;
                    }));
                }
            }
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
        if (_actions.count(action) > 0 && _actions.find(action)->second.justInput && _actions.find(action)->second.pressed)
        {
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
            return true;
        }

        return false;
    }

    // check if action is released
    bool ActionMap::isReleased(const std::string& action) const
    {
        if (_actions.count(action) > 0  && !_actions.find(action)->second.pressed)
        {
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
                    if (!_actions.find(action.name)->second.pressed){ // set justInput to true if wasnt pressed already
                        _actions.find(action.name)->second.justInput = true;
                    }
                    _actions.find(action.name)->second.pressed = true; // set pressed to true
                }
                return;
            }
            for (const auto& action : _inputKeys.find(inputKey)->second) // if we release
            {
                if(_actions.find(action.name)->second.pressed){ // set justInput to true if wasn't released already
                    _actions.find(action.name)->second.justInput = true;
                }
                _actions.find(action.name)->second.pressed = false; // set pressed to false (released)
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



void ActionMap::setActionPressed(const std::string& action, bool pressed, bool justInput) {
    if(_actions.find(action) != _actions.end()){
        _actions[action].pressed = pressed;
        _actions[action].justInput = justInput;
    }
}
