//
// Created by user on 12/13/2022.
//

#include "GameManagerScript.h"
#include "Input/ActionMap.h"
#include <iostream>

void GameManagerScript::restartLevel() {
    // TODO restart level by loading begin state
    std::cout << "restart level" << std::endl;
}

void GameManagerScript::tryFinishLevel() {
    // TODO check if all enemies have died before calling finishLevel()
    finishLevel();
}

void GameManagerScript::finishLevel() {
    // TODO finish the level by showing replay
    std::cout << "finish" << std::endl;
}

void GameManagerScript::onUpdate() {
    if(ActionMap::getActionMap()->isJustPressed("restart"))
        restartLevel();
}
