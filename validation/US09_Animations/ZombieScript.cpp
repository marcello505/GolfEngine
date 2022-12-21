//
// Created by conner on 11/24/2022.
//

#include "ZombieScript.h"

using namespace GolfEngine;

void ZombieScript::onStart() {
    animator = _gameObject->get().getComponent<Animator>();
}

void ZombieScript::onUpdate() {
    timePassed += Core::Time::getPhysicsDeltaTime();
    if(timePassed > 3.0f){
        timePassed = 0;
        animator->get().play("moving");
    }
}
