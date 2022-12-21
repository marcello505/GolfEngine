//
// Created by conner on 12/15/2022.
//

#include "GameManager.h"
#include "../scripts/GameManagerScript.h"

GameManager::GameManager(const std::string& nextLevelName) {
    tag = "GameManager";
    addComponent<GameManagerScript>(nextLevelName);
}
