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

    if(_gameObject->get().hasComponent<GolfEngine::Scene::Components::AudioSource>())
        _audioSource = &_gameObject->get().getComponent<GolfEngine::Scene::Components::AudioSource>();

    if(_gameObject->get().hasComponent<ParticleSystem>())
        _particleSystem = &_gameObject->get().getComponent<ParticleSystem>();
}

void PlayerCollisionScript::onCollisionEnter(RigidBody &other) {
    if(other.getParentGameObject()->tag == "enemy"){
        // Play some death effects and disable player controls
        // TODO maybe change sprite/animation
        _audioSource->play("death", false);
        _particleSystem->play(false);
        _playerMovement->setActive(false);
        _playerShoot->setActive(false);
    }
}

void PlayerCollisionScript::onAreaEnter(RigidBody &other) {
    if(other.getParentGameObject()->tag == "finish"){
        _gameManager->tryFinishLevel();
    }
}
