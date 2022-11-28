//
// Created by conner on 11/24/2022.
//

#include "ZombieScript.h"

void ZombieScript::onStart() {
    animator = _gameObject->get().getComponent<Animator>();
}

void ZombieScript::onUpdate() {
    timePassed += GolfEngine::Time::getPhysicsDeltaTime();
    if(timePassed > 3.0f){
        timePassed = 0;
        animator->get().play("attack");
    }
}
