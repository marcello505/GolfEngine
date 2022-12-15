//
// Created by user on 12/13/2022.
//

#include "GameManagerScript.h"
#include "Input/ActionMap.h"
#include "Core/SceneManager.h"
#include <iostream>

void GameManagerScript::restartLevel() {
    GolfEngine::SceneManager::GetSceneManager().getCurrentScene().loadCurrentSceneState(1);
}

void GameManagerScript::tryFinishLevel() {
    // TODO check if all enemies have died before calling finishLevel()
    finishLevel();
}

void GameManagerScript::finishLevel() {
    // TODO finish the level by showing replay
    std::cout << "finish" << std::endl;
}

void GameManagerScript::onStart() {
    GolfEngine::SceneManager::GetSceneManager().getCurrentScene().saveCurrentSceneState(1);
}

void GameManagerScript::onUpdate() {
    if(ActionMap::getActionMap()->isJustPressed("restart"))
        restartLevel();
}

