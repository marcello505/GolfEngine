//
// Created by Lucas on 12-12-2022.
//

#include "EnemyMovementScript.h"
#include "Services/Singletons/PhysicsSingleton.h"

EnemyMovementScript::EnemyMovementScript(GameObject* target) : _target{*target}  {

}
void EnemyMovementScript::onStart() {
    pathfinding = _gameObject->get().getComponent<Pathfinding>();
}

void EnemyMovementScript::onUpdate() {
    rotateEnemy();
    if(true) {
        auto direction = pathfinding->get().getNewDirection();
        auto rb = &_gameObject.value().get().getComponent<RigidBody>();
        rb->applyWorldForceToCenter(direction * 0.5);
    } else{
        chasing = checkIftargetIsInSight();
    }
}

bool EnemyMovementScript::checkIftargetIsInSight() {
    auto pos =  _gameObject->get().getWorldTransform().position;
    auto targetPos =  _target.getWorldTransform().position;
    if(GolfEngine::Services::Physics::hasService()){
      auto ps =  GolfEngine::Services::Physics::getService();
      ps->raycastWorld(&_gameObject->get().getComponent<RigidBody>(), &_target.getComponent<RigidBody>());


    }
    return false;
}

void EnemyMovementScript::rotateEnemy() {

    float angleToMouse = _gameObject->get().getWorldTransform().position.angleToDegrees(_target.getWorldTransform().position);
    _gameObject->get().setLocalRotation(angleToMouse);
}


