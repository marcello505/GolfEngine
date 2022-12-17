//
// Created by Lucas on 16-12-2022.
//

#include "EnemyCollisionScript.h"
#include "EnemyMovementScript.h"
#include "../gameobjects/EnemyObject.h"

void EnemyCollisionScript::onStart() {
    if(_gameObject->get().hasComponent<EnemyMovementScript>())
        _enemyMovement = &_gameObject->get().getComponent<EnemyMovementScript>();

}
void EnemyCollisionScript::onUpdate() {
    if(_death)
        _gameObject->get().setActive(false);
}

void EnemyCollisionScript::onCollisionEnter(RigidBody &other) {
    if(other.getParentGameObject()->tag == "projectile"){
        // TODO add some "death" effects (maybe change to a death animation?)
        _death = true;
    }
}

std::unique_ptr<ISnapshot> EnemyCollisionScript::saveSnapshot() {
    auto snapshot = std::make_unique<Snapshot>();

    snapshot->death = _death;
    return snapshot;
}

void EnemyCollisionScript::loadSnapshot(const ISnapshot& rawSnapshot) {
    auto& snapshot = (const Snapshot&)rawSnapshot;

    _death = snapshot.death;
}


