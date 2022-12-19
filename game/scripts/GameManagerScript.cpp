//
// Created by user on 12/13/2022.
//
#include <iostream>

#include "Input/ActionMap.h"
#include "Core/SceneManager.h"
#include <iostream>
#include <Core/Time.h>
#include <Core/Settings.h>

#include "../utils/GameActions.h"
#include "GameManagerScript.h"
#include "EnemyCollisionScript.h"

using namespace GolfEngine;

void GameManagerScript::restartLevel() {
    _timePassed = 0.0f;
    _levelFinished = false;
    Core::SceneManager::GetSceneManager().getCurrentScene().loadCurrentSceneState(1);
    startRecordingReplay();
}

void GameManagerScript::tryFinishLevel() {
    auto enemyGameObjects = Core::SceneManager::GetSceneManager().getCurrentScene().getGameObjectsWithTag("enemy");
    bool allEnemiesDead {true};

    for(const auto& enemy : enemyGameObjects){
        if(enemy.get().hasComponent<EnemyCollisionScript>() && !enemy.get().getComponent<EnemyCollisionScript>().isDead()){
            allEnemiesDead = false;
            break;
        }
    }

    if(allEnemiesDead)
        finishLevel();
}

void GameManagerScript::finishLevel() {
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
    _levelFinished = true;
    Core::SceneManager::GetSceneManager().getCurrentScene().playReplay();
}

void GameManagerScript::onStart() {
    _highScoreKey = Core::SceneManager::GetSceneManager().getCurrentSceneName() + "HighScore";
    Core::SceneManager::GetSceneManager().getCurrentScene().saveCurrentSceneState(1);
    startRecordingReplay();
}

void GameManagerScript::onUpdate() {
    Input::ActionMap* actionMap = Input::ActionMap::getActionMap();
    if(!_levelFinished)
        _timePassed += Core::Time::getPhysicsDeltaTime();

    if(actionMap->isJustPressed(ACTION_GAME_MANAGER_RESTART))
        restartLevel();
    else if(actionMap->isJustPressed(ACTION_GAME_MANAGER_TIME_SCALE_UP))
        Core::Time::setTimeScale(Core::Time::getTimeScale() + 0.1f);
    else if(actionMap->isJustPressed(ACTION_GAME_MANAGER_TIME_SCALE_DOWN))
        Core::Time::setTimeScale(Core::Time::getTimeScale() - 0.1f);
    else if(actionMap->isJustPressed(ACTION_GAME_MANAGER_TIME_SCALE_RESET))
        Core::Time::setTimeScale(1.0f);

    //Exit level logic
    {
        if(_waitingForQuitConfirmation) _quitConfirmationTimePassed += Core::Time::getPhysicsDeltaTime();

        if(!_waitingForQuitConfirmation && actionMap->isJustPressed(ACTION_GAME_MANAGER_EXIT)){
            //Esc was pressed once
            _waitingForQuitConfirmation = true;
            _quitConfirmationTimePassed = 0.0f;
        }
        else if(_waitingForQuitConfirmation && actionMap->isJustPressed(ACTION_GAME_MANAGER_EXIT)){
            //Escape level
            Core::SceneManager::GetSceneManager().getCurrentScene().stopReplay();
            Core::SceneManager::GetSceneManager().loadScene("mainMenu");
        }
        else if(_waitingForQuitConfirmation && _quitConfirmationTimePassed >= 3.0f){
            _waitingForQuitConfirmation = false;
        }
    }

    //Finished level logic
    if(_levelFinished && actionMap->isJustPressed(ACTION_GAME_MANAGER_NEXT)){
        Core::SceneManager::GetSceneManager().getCurrentScene().stopReplay();
        Core::SceneManager::GetSceneManager().loadScene(_nextLevelName);
    }

}

void GameManagerScript::startRecordingReplay() {
    Core::SceneManager::GetSceneManager().getCurrentScene().stopReplay();
    Core::SceneManager::GetSceneManager().getCurrentScene().startRecordingReplay(_playerActionsToLock, true);
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

bool GameManagerScript::isWaitingForQuitConfirmation() const {
    return _waitingForQuitConfirmation;
}

bool GameManagerScript::isLevelFinished() const {
    return _levelFinished;
}

