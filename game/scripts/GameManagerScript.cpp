//
// Created by user on 12/13/2022.
//

#include "GameManagerScript.h"
#include "Input/ActionMap.h"
#include "Core/SceneManager.h"
#include <iostream>
#include <Core/Time.h>
#include <Core/Settings.h>

void GameManagerScript::restartLevel() {
    _timePassed = 0.0f;
    GolfEngine::SceneManager::GetSceneManager().getCurrentScene().loadCurrentSceneState(1);
}

void GameManagerScript::tryFinishLevel() {
    // TODO check if all enemies have died before calling finishLevel()
    finishLevel();
}

void GameManagerScript::finishLevel() {
    // TODO finish the level by showing replay
    std::cout << "finish" << std::endl;

    // Check if there is an existing high score
    if(GolfEngine::Core::getProjectSettings().hasFloat(_highScoreKey)){
        // Get previous high score and check if it has been beaten
        float prevHighScore = GolfEngine::Core::getProjectSettings().getFloat(_highScoreKey);
        if(_timePassed < prevHighScore){
            // Update high score
            GolfEngine::Core::getProjectSettings().setFloat(_highScoreKey, _timePassed);
        }
    }
    else {
        // First time level has been completed, create high score entry
        GolfEngine::Core::getProjectSettings().setFloat(_highScoreKey, _timePassed);
    }
}

void GameManagerScript::onStart() {
    _highScoreKey = GolfEngine::SceneManager::GetSceneManager().getCurrentSceneName() + "HighScore";
    GolfEngine::SceneManager::GetSceneManager().getCurrentScene().saveCurrentSceneState(1);
}

void GameManagerScript::onUpdate() {
    _timePassed += GolfEngine::Time::getPhysicsDeltaTime();

    if(ActionMap::getActionMap()->isJustPressed("restart"))
        restartLevel();

    if(ActionMap::getActionMap()->isJustPressed("backToMenu"))
        GolfEngine::SceneManager::GetSceneManager().loadScene("mainMenu"); //go to main menu
}

float GameManagerScript::getTimePassed() const {
    return _timePassed;
}

float GameManagerScript::getHighScoreTime() const {
    if(GolfEngine::Core::getProjectSettings().hasFloat(_highScoreKey)){
        return GolfEngine::Core::getProjectSettings().getFloat(_highScoreKey);
    }
    return 0.0f;
}

