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

void GameManagerScript::restartLevel() {
    _timePassed = 0.0f;
    GolfEngine::SceneManager::GetSceneManager().getCurrentScene().loadCurrentSceneState(1);
    startRecordingReplay();
}

void GameManagerScript::tryFinishLevel() {
    auto enemyGameObjects = GolfEngine::SceneManager::GetSceneManager().getCurrentScene().getGameObjectsWithTag("enemy");
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
    GolfEngine::SceneManager::GetSceneManager().getCurrentScene().playReplay();
}

void GameManagerScript::onStart() {
    _highScoreKey = GolfEngine::SceneManager::GetSceneManager().getCurrentSceneName() + "HighScore";
    GolfEngine::SceneManager::GetSceneManager().getCurrentScene().saveCurrentSceneState(1);
    startRecordingReplay();
}

void GameManagerScript::onUpdate() {
    ActionMap* actionMap = ActionMap::getActionMap();
    _timePassed += GolfEngine::Time::getPhysicsDeltaTime();

    if(actionMap->isJustPressed(ACTION_GAME_MANAGER_RESTART))
        restartLevel();
    else if(actionMap->isJustPressed(ACTION_GAME_MANAGER_TIME_SCALE_UP))
        GolfEngine::Time::setTimeScale(GolfEngine::Time::getTimeScale() + 0.1f);
    else if(actionMap->isJustPressed(ACTION_GAME_MANAGER_TIME_SCALE_DOWN))
        GolfEngine::Time::setTimeScale(GolfEngine::Time::getTimeScale() - 0.1f);
    else if(actionMap->isJustPressed(ACTION_GAME_MANAGER_TIME_SCALE_RESET))
        GolfEngine::Time::setTimeScale(1.0f);
}

void GameManagerScript::startRecordingReplay() {
    GolfEngine::SceneManager::GetSceneManager().getCurrentScene().startRecordingReplay(_playerActionsToLock, true);
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

