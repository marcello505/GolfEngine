//
// Created by Lucas on 28-11-2022.
//

#include "ParticleScript.h"
#include "Input/ActionMap.h"
#include "Scene/Components/ParticleSystem.h"

void ParticleScript::onUpdate() {

    if(ActionMap::getActionMap()->isPressed("Stop")){
         _gameObject->get().getComponent<ParticleSystem>().stop();
    }
    if(ActionMap::getActionMap()->isPressed("Start")){
         _gameObject->get().getComponent<ParticleSystem>().play(true);
    }
}
