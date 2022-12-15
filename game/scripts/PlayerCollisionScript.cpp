//
// Created by conner on 12/13/2022.
//

#include "Core/SceneManager.h"
#include "PlayerCollisionScript.h"
#include <iostream>

void PlayerCollisionScript::onStart() {
    auto& gm = GolfEngine::SceneManager::GetSceneManager().getCurrentScene().getGameObjectWithTag("GameManager");
    _gameManager = &gm.getComponent<GameManagerScript>();

    if(_gameObject->get().hasComponent<PlayerMovementScript>())
        _playerMovement = &_gameObject->get().getComponent<PlayerMovementScript>();

    if(_gameObject->get().hasComponent<PlayerShootScript>())
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
