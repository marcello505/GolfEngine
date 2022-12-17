//
// Created by user on 12/13/2022.
//
#include <iostream>

#include "Input/ActionMap.h"
#include "Core/SceneManager.h"

#include "GameManagerScript.h"
#include "EnemyCollisionScript.h"

void GameManagerScript::restartLevel() {
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
    GolfEngine::SceneManager::GetSceneManager().getCurrentScene().playReplay();
}

void GameManagerScript::onStart() {
    GolfEngine::SceneManager::GetSceneManager().getCurrentScene().saveCurrentSceneState(1);
    startRecordingReplay();
}

void GameManagerScript::onUpdate() {
    if(ActionMap::getActionMap()->isJustPressed("restart"))
        restartLevel();
}

void GameManagerScript::startRecordingReplay() {
    GolfEngine::SceneManager::GetSceneManager().getCurrentScene().startRecordingReplay(_playerActionsToLock, true);
}

