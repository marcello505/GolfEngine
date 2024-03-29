//
// Created by conner on 12/15/2022.
//

#include <Core/SceneManager.h>
#include <Core/Time.h>
#include <Input/ActionMap.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "HUDScript.h"
#include "../gameobjects/PlayerObject.h"

using namespace GolfEngine;

HUDScript::HUDScript(Text* fpsText, Text* timeText, Text* highScoreTimeText, Text* quitConfirmationText,
                     Text* levelCompleteText, Text* youDiedText, Text* ammoCounterText)
        : _fpsText{fpsText},
        _timeText{timeText},
        _highScoreTimeText{highScoreTimeText},
        _quitConfirmationText{quitConfirmationText},
        _levelCompleteText{levelCompleteText},
        _youDiedText{youDiedText},
        _ammoCounterText{ammoCounterText},
        _renderFPS{false} {
    _gameManager = &Core::SceneManager::GetSceneManager().getCurrentScene().getGameObjectWithTag("GameManager").getComponent<GameManagerScript>();
    _playerShootScript = &Core::SceneManager::GetSceneManager().getCurrentScene().getGameObjectWithTag(TAG_PLAYER).getComponent<PlayerShootScript>();
}

void HUDScript::onStart() {
    updateHighScoreText();
}

void HUDScript::onUpdate() {
    if(Input::ActionMap::getActionMap()->isJustPressed("renderFPS")){
        _renderFPS = !_renderFPS;
        _fpsText->_renderShape.setText("");
    }

    // Update fps text
    if(_renderFPS){
        // Retrieve fps, convert to string and update text
        std::string fps = std::to_string(static_cast<int>(Core::Time::getRenderFps()));
        _fpsText->_renderShape.setText("FPS " + fps);
    }

    // Update time text
    float timePassed = _gameManager->getTimePassed();
    std::stringstream time {};
    time << std::setw(2) << std::setfill('0') << (int)timePassed/60; // Minutes
    time << ':';
    time << std::setw(2) << std::setfill('0') << (int)timePassed%60; // Seconds
    time << ':';
    time << std::setw(2) << std::setfill('0') << (int)(timePassed*100) % 100; // Milliseconds
    _timeText->_renderShape.setText(time.str());

    // Update quit confirmation text
    if(_gameManager->isWaitingForQuitConfirmation()){
        _quitConfirmationText->_renderShape.setText("Are you sure you want to quit? Press ESC again to confirm.");
    }
    else{
        _quitConfirmationText->_renderShape.setText("");
    }

    // Update level finished text
    if(_gameManager->isLevelFinished()){
        updateHighScoreText();
        _levelCompleteText->_renderShape.setText("Level Complete! Press space to continue.");
    }
    else{
        _levelCompleteText->_renderShape.setText("");
    }

    // Update you died text
    if(!_playerShootScript->isAlive()){
        _youDiedText->_renderShape.setText("You Died! Press BackSpace to Restart");
    }
    else{
        _youDiedText->_renderShape.setText("");
    }

    // Update ammo counter text
    _ammoCounterText->_renderShape.setText((std::stringstream{} << _playerShootScript->getCurrentAmmo()).str());
}

void HUDScript::updateHighScoreText() {
    // Update high score text
    float highScore = _gameManager->getHighScoreTime();
    if(highScore > 0){
        std::stringstream time {};
        time << std::setw(2) << std::setfill('0') << (int)highScore/60; // Minutes
        time << ':';
        time << std::setw(2) << std::setfill('0') << (int)highScore%60; // Seconds
        time << ':';
        time << std::setw(2) << std::setfill('0') << (int)(highScore*100) % 100; // Milliseconds
        _highScoreTimeText->_renderShape.setText(time.str());
    }
}
