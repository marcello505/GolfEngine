//
// Created by conner on 12/13/2022.
//

#include "Core/SceneManager.h"
#include "PlayerCollisionScript.h"
#include <iostream>

void PlayerCollisionScript::onStart() {
    auto& gm = GolfEngine::Core::SceneManager::GetSceneManager().getCurrentScene().getGameObjectWithTag("GameManager");
    _gameManager = &gm.getComponent<GameManagerScript>();

    if(_gameObject->get().hasComponent<PlayerMovementScript>())
        _playerMovement = &_gameObject->get().getComponent<PlayerMovementScript>();

    if(_gameObject->get().hasComponent<PlayerShootScript>())
        _playerShoot = &_gameObject->get().getComponent<PlayerShootScript>();

    if(_gameObject->get().hasComponent<GolfEngine::Scene::Components::AudioSource>())
        _audioSource = &_gameObject->get().getComponent<GolfEngine::Scene::Components::AudioSource>();

    // Get blood splatter particle system from child
    auto& children = _gameObject->get().children();
    if(!children.empty()){
        for(auto& c : children){
            if(c.get().name == "blood splatter"){
                if(c.get().hasComponent<ParticleSystem>()){
                    _particleSystem = &c.get().getComponent<ParticleSystem>();
                    break;
                }
            }
        }
    }
}

void PlayerCollisionScript::onCollisionEnter(RigidBody &other) {
    if(other.getParentGameObject()->tag == "enemy"){
        // TODO maybe change sprite/animation
        // Play some death effects and disable player controls
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
