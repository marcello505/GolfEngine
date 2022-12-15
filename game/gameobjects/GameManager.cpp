//
// Created by conner on 12/15/2022.
//

#include "GameManager.h"
#include "../scripts/GameManagerScript.h"

GameManager::GameManager() {
    tag = "GameManager";
    addComponent<GameManagerScript>();
}
