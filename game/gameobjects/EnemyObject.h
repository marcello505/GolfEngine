//
// Created by Lucas on 12-12-2022.
//

#ifndef GOLFENGINE_ENEMYOBJECT_H
#define GOLFENGINE_ENEMYOBJECT_H


#include "Scene/GameObjects/GameObject.h"
#include "PlayerObject.h"

class EnemyObject : public GameObject{

public:
    EnemyObject(GameObject *target);
};


#endif //GOLFENGINE_ENEMYOBJECT_H
