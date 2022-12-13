//
// Created by Lucas on 12-12-2022.
//

#include "EnemyObject.h"
#include "Scene/Components/BoxCollider.h"
#include "Scene/Components/RigidBody.h"
#include "Scene/Components/SpriteComponent.h"
#include "Scene/Components/Animator.h"
#include "../scripts/EnemyMovementScript.h"
#include "Scene/Components/AudioSource.h"
#include "Scene/Components/Pathfinding.h"

EnemyObject::EnemyObject(GameObject *target) {
    addComponent<BoxCollider>(Vector2{12.5f, 12.5f});

//
    auto& animator = addComponent<Animator>("res/sprite_sheets/zombie.png", 7, 7, Vector2(239, 221), Vector2(20,20));
    animator.addAnimation("attack", 0, 8, 15.0f);
    animator.addAnimation("idle", 9, 25, 15.0f);
    animator.addAnimation("moving", 26, 42, 15.0f);
    animator.addReturnTransition("attack", "idle");
    animator.play("idle", true);
//
    RigidBodyDef rbDef {};
 //   rbDef.fixedRotation = true;
    rbDef.linearDamping = 5.0f;
    addComponent<RigidBody>(rbDef);
    addComponent<GolfEngine::Scene::Components::AudioSource>("res/audio/Zombie-Sound.ogg", false);
    addComponent<Pathfinding>(target);
    addComponent<EnemyMovementScript>(target);

}
