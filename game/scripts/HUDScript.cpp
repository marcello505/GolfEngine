//
// Created by conner on 12/15/2022.
//

#include <Core/Time.h>
#include <Input/ActionMap.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "HUDScript.h"

HUDScript::HUDScript(Text* fpsText, Text* timeText) : _fpsText{fpsText}, _timeText{timeText}, _renderFPS{false}, _timePassed{0.0f} {
}

void HUDScript::onUpdate() {
    if(ActionMap::getActionMap()->isJustPressed("renderFPS")){
        _renderFPS = !_renderFPS;
        _fpsText->_renderShape.setText("");
    }

    // Update fps text
    if(_renderFPS){
        // Retrieve fps, convert to string and update text
        std::string fps = std::to_string(static_cast<int>(GolfEngine::Time::getRenderFps()));
        _fpsText->_renderShape.setText("FPS " + fps);
    }

    // Update time text
    _timePassed += GolfEngine::Time::getPhysicsDeltaTime();
    std::stringstream time {};
    time << std::setw(2) << std::setfill('0') << (int)_timePassed/60; // Minutes
    time << ':';
    time << std::setw(2) << std::setfill('0') << (int)_timePassed%60; // Seconds
    time << ':';
    time << std::setw(2) << std::setfill('0') << (int)(_timePassed*100) % 100; // Milliseconds
    _timeText->_renderShape.setText(time.str());
}
