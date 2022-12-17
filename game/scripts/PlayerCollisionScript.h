//
// Created by conner on 12/13/2022.
//

#ifndef GOLFENGINE_PLAYERCOLLISIONSCRIPT_H
#define GOLFENGINE_PLAYERCOLLISIONSCRIPT_H

#include "Scene/Components/BehaviourScript.h"
#include <Scene/Components/ParticleSystem.h>
#include <Scene/Components/AudioSource.h>
#include "GameManagerScript.h"
#include "PlayerMovementScript.h"
#include "PlayerShootScript.h"

class PlayerCollisionScript : public BehaviourScript {
    void onStart() override;
    void onCollisionEnter(RigidBody& other) override;
    void onAreaEnter(RigidBody& other) override;
private:
    GameManagerScript* _gameManager;
    PlayerMovementScript* _playerMovement;
    PlayerShootScript* _playerShoot;
    GolfEngine::Scene::Components::AudioSource* _audioSource;
    ParticleSystem* _particleSystem;
};


#endif //GOLFENGINE_PLAYERCOLLISIONSCRIPT_H
