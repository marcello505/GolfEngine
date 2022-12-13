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
    if(chasing) {
        auto direction = pathfinding->get().getNewDirection();
        auto rb = &_gameObject.value().get().getComponent<RigidBody>();
        rb->applyLocalForceToCenter(direction * 0.5);
    } else{
        chasing = checkIftargetIsInSight();
    }
}

bool EnemyMovementScript::checkIftargetIsInSight() {
    auto pos =  _gameObject->get().getWorldTransform().position;
    auto targetPos =  _target.getWorldTransform().position;
    if(GolfEngine::Services::Physics::hasService()){
      auto colliders =  GolfEngine::Services::Physics::getService()->getStaticColliders();

      

    }


}


