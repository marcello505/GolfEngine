//
// Created by Lucas on 12-12-2022.
//

#include "EnemyObject.h"
#include "Scene/Components/BoxCollider.h"
#include "Scene/Components/RigidBody.h"
#include "Scene/Components/SpriteComponent.h"
#include "Scene/Components/Animator.h"
#include "../scripts/EnemyMovementScript.h"
#include "../scripts/EnemyCollisionScript.h"
#include "Scene/Components/AudioSource.h"
#include "Scene/Components/Pathfinding.h"
#include "Scene/Components/ParticleSystem.h"
#include "BloodSplatterParticleEffect.h"

EnemyObject::EnemyObject(GameObject *target, Scene& scene){
    tag = "enemy";
    addComponent<BoxCollider>(Vector2{12.5f, 12.5f});

//
    addComponent<SpriteComponent>("res/sprite_sheets/zombie.png", Vector2{2, 2}, Rect2{{}, {239, 221}});
    auto& animator = addComponent<Animator>("res/sprite_sheets/zombie.png", 7, 7, Vector2(239, 221), Vector2(2,2));
    animator.addAnimation("attack", 0, 8, 15.0f);
    animator.addAnimation("idle", 9, 25, 15.0f);
    animator.addAnimation("moving", 26, 42, 15.0f);
    animator.addReturnTransition("attack", "idle");
    animator.play("idle", true);
//
    RigidBodyDef rbDef {};
    rbDef.linearDamping = 5.0f;
    addComponent<RigidBody>(rbDef);
    addComponent<GolfEngine::Scene::Components::AudioSource>("res/audio/Zombie-Sound.ogg", false);
    addComponent<Pathfinding>(target);
    addComponent<EnemyMovementScript>(target);
    addComponent<EnemyCollisionScript>();

    // Blood splatter particle effect game object
    scene.createNewGameObject<BloodSplatterParticleEffect>((GameObject&)*this);

}

void EnemyObject::addPatrolPoint(Vector2 point) {
    patrolPoints.emplace_back(point);
}
