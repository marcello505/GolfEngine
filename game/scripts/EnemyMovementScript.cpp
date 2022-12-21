//
// Created by Lucas on 12-12-2022.
//

#include "EnemyMovementScript.h"
#include "Services/Singletons/PhysicsSingleton.h"
#include "../gameobjects/EnemyObject.h"
#include "Scene/Components/Animator.h"

EnemyMovementScript::EnemyMovementScript(GameObject* target) : _target{*target}  {
}

void EnemyMovementScript::onStart() {
    if(_gameObject->get().hasComponent<Pathfinding>())
        _pathfinding = _gameObject->get().getComponent<Pathfinding>();

    if(_gameObject->get().hasComponent<AudioSource>())
        _audioSource = &_gameObject->get().getComponent<AudioSource>();
}

void EnemyMovementScript::onUpdate() {

    if(_chasing) {
        _gameObject->get().getComponent<Animator>().play("moving",true);
        rotateEnemyToPosition(_target.getWorldTransform().position);
        _direction = _pathfinding->get().getPathDirection();
        auto rb = &_gameObject.value().get().getComponent<RigidBody>();
        rb->applyWorldForceToCenter(_direction * 1);
    }else{
        _chasing = checkIftargetIsInSight();
        // Play sfx for spotting player
        if(_chasing)
            _audioSource->play("spotted");

        auto& enemyObject = (EnemyObject &) _gameObject->get();
        if(!enemyObject.patrolPoints.empty()) {
            _gameObject->get().getComponent<Animator>().play("moving",true);

            auto currPos = enemyObject.getWorldTransform().position;
            if(static_cast<int>(currPos.x) == enemyObject.patrolPoints.at(_patrolIndex).x && static_cast<int>(currPos.y) == enemyObject.patrolPoints.at(_patrolIndex).y){
                if (_patrolIndex == enemyObject.patrolPoints.size()-1 ){
                    _patrolIndex = 0;
                }else {
                    _patrolIndex++;
                }
            }
            rotateEnemyToPosition(enemyObject.patrolPoints.at(_patrolIndex));

            _direction = _pathfinding->get().getDirection(enemyObject.patrolPoints.at(_patrolIndex));
            auto rb = &_gameObject.value().get().getComponent<RigidBody>();
            rb->applyWorldForceToCenter(_direction *0.1);
        }
    }
}

bool EnemyMovementScript::checkIftargetIsInSight() {
    if(GolfEngine::Services::Physics::hasService()){
      auto ps =  GolfEngine::Services::Physics::getService();
        return ps->raycastWorld(&_gameObject->get().getComponent<RigidBody>(),&_target.getComponent<RigidBody>());
    }
    return false;
}

void EnemyMovementScript::rotateEnemyToPosition(Vector2 targetPosition) {
    float angleToPoint = _gameObject->get().getWorldTransform().position.angleToDegrees(targetPosition);
    _gameObject->get().setLocalRotation(angleToPoint);
}

std::unique_ptr<ISnapshot> EnemyMovementScript::saveSnapshot() {
    auto result = std::make_unique<Snapshot>();
    result->chasing = _chasing;
    result->patrolIndex = _patrolIndex;
    result->direction = _direction;
    return result;
}

void EnemyMovementScript::loadSnapshot(const ISnapshot& rawSnapshot) {
    auto& snapshot = (Snapshot&)rawSnapshot;
    _chasing = snapshot.chasing;
    _patrolIndex = snapshot.patrolIndex;
    _direction = snapshot.direction;
}


