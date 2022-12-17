//
// Created by conner on 12/15/2022.
//

#ifndef GOLFENGINE_GAMEMANAGER_H
#define GOLFENGINE_GAMEMANAGER_H

#include "Scene/GameObjects/GameObject.h"

class GameManager : public GameObject{
public:
    GameManager(const std::string& nextLevelName);
};


#endif //GOLFENGINE_GAMEMANAGER_H
