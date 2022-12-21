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

using namespace GolfEngine::Input;
using namespace GolfEngine::Scene::Components;

class PlayerMovementScript : public BehaviourScript {
private:
    struct Snapshot : public ISnapshot{
        bool active {};
    };
public:
    void onStart() override;
    void onUpdate() override;

    std::unique_ptr<ISnapshot> saveSnapshot() override;
    void loadSnapshot(const ISnapshot &rawSnapshot) override;

    float playerSpeed {4.0f};
private:
    SpriteComponent* _sprite {};
    RigidBody* _rb {};
    ActionMap* _actionMap {};
    Animator* _animator {};

    float rotationOffset {5.0f};
};


#endif //GOLFENGINE_PLAYERMOVEMENTSCRIPT_H
