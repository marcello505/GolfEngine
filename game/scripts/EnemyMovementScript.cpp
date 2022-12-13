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
    pathfinding = _gameObject->get().getComponent<Pathfinding>();
}

void EnemyMovementScript::onUpdate() {

    if(chasing) {
        _gameObject->get().getComponent<Animator>().play("moving",true);
        rotateEnemyToPosition(_target.getWorldTransform().position);
        direction = pathfinding->get().getPathDirection();
        auto rb = &_gameObject.value().get().getComponent<RigidBody>();
        rb->applyWorldForceToCenter(direction * 0.5);
    }else{
        chasing = checkIftargetIsInSight();
        auto& enemyObject = (EnemyObject &) _gameObject->get();
        if(!enemyObject.patrolPoints.empty()) {
            _gameObject->get().getComponent<Animator>().play("moving",true);

            auto currPos = enemyObject.getWorldTransform().position;
            if(static_cast<int>(currPos.x) == enemyObject.patrolPoints.at(patrolIndex).x && static_cast<int>(currPos.y) == enemyObject.patrolPoints.at(patrolIndex).y){
                if (patrolIndex == enemyObject.patrolPoints.size()-1 ){
                    patrolIndex = 0;
                }else {
                    patrolIndex++;
                }
            }
            rotateEnemyToPosition(enemyObject.patrolPoints.at(patrolIndex));

            direction = pathfinding->get().getDirection(enemyObject.patrolPoints.at(patrolIndex));
            auto rb = &_gameObject.value().get().getComponent<RigidBody>();
            rb->applyWorldForceToCenter(direction *0.1);
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
    result->chasing = chasing;
    return result;
}

void EnemyMovementScript::loadSnapshot(const ISnapshot& rawSnapshot) {
    auto& snapshot = (Snapshot&)rawSnapshot;
    chasing = snapshot.chasing;
}


