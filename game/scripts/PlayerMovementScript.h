//
// Created by marcello on 11/29/22.
//

#ifndef GOLFENGINE_PLAYERMOVEMENTSCRIPT_H
#define GOLFENGINE_PLAYERMOVEMENTSCRIPT_H

#include <Scene/Components/BehaviourScript.h>
#include <Scene/Components/RigidBody.h>
#include <Scene/Components/AudioSource.h>
#include <Scene/Components/SpriteComponent.h>
#include <Input/ActionMap.h>

#include "../scripts/ProjectilePoolScript.h"
#include "Scene/Components/Animator.h"

class PlayerMovementScript : public BehaviourScript {
public:
    explicit PlayerMovementScript(ProjectilePoolScript* projectilePoolScript) : _projectilePool{projectilePoolScript} {}
    void onStart() override;
    void onUpdate() override;

    float playerSpeed {1.0f};
private:
    SpriteComponent* _sprite {};
    RigidBody* _rb {};
    ActionMap* _actionMap {};
    Animator* _animator {};
    ProjectilePoolScript* _projectilePool {};
    GolfEngine::Scene::Components::AudioSource* _gunShotAudio {};
};


#endif //GOLFENGINE_PLAYERMOVEMENTSCRIPT_H
