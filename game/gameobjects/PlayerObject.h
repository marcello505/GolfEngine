//
// Created by marcello on 11/29/22.
//

#ifndef GOLFENGINE_PLAYEROBJECT_H
#define GOLFENGINE_PLAYEROBJECT_H


#include "../scripts/ProjectilePoolScript.h"
#include "Scene/GameObjects/GameObject.h"
#include "../scripts/PlayerMovementScript.h"
#include "../scripts/PlayerShootScript.h"
#include "Scene/Scene.h"

#define TAG_PLAYER "player"

using namespace GolfEngine::Scene;

class PlayerObject : public GameObject {
public:
    explicit PlayerObject(ProjectilePoolScript* projectilePoolScript, Scene& scene);
};


#endif //GOLFENGINE_PLAYEROBJECT_H
