//
// Created by conner on 12/13/2022.
//

#include "PlayerCollisionScript.h"
#include <iostream>

void PlayerCollisionScript::onStart() {
    _gameManager = &_gameObject->get().getComponent<GameManagerScript>();
    _playerMovement = &_gameObject->get().getComponent<PlayerMovementScript>();
    _playerShoot = &_gameObject->get().getComponent<PlayerShootScript>();
}

void PlayerCollisionScript::onCollisionEnter(RigidBody &other) {
    if(other.getParentGameObject()->tag == "enemy"){
        // TODO add some "death" effects (maybe change to a death animation?)
        _playerMovement->setActive(false);
        _playerShoot->setActive(false);
    }
}

void PlayerCollisionScript::onAreaEnter(RigidBody &other) {
    if(other.getParentGameObject()->tag == "finish"){
        _gameManager->tryFinishLevel();
    }
}
