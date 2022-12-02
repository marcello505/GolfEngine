//
// Created by marcello on 11/29/22.
//

#ifndef GOLFENGINE_PLAYEROBJECT_H
#define GOLFENGINE_PLAYEROBJECT_H


#include "../scripts/ProjectilePoolScript.h"
#include "Scene/GameObjects/GameObject.h"

class PlayerObject : public GameObject {
public:
    PlayerObject(ProjectilePoolScript* projectilePoolScript, bool useAnimator);

};


#endif //GOLFENGINE_PLAYEROBJECT_H
