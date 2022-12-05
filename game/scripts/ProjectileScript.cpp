//
// Created by marcello on 12/1/22.
//

#include "ProjectileScript.h"

void ProjectileScript::onStart() {
    _rigidBody = &_gameObject.value().get().getComponent<RigidBody>();
    _gameObject.value().get().setActive(false);
}

void ProjectileScript::onUpdate() {
    if(_ticksToLive < 30){
        _rigidBody->setLinearVelocity(_dir * 20.0f);
        _ticksToLive++;
    }
    else{
        _gameObject->get().setActive(false);
    }
}

void ProjectileScript::shoot(const Transform& transform, const Vector2& direction) {
    _dir = direction.normalized();
    _gameObject->get().setActive(true);
    _rigidBody->setTransform(transform);
    _rigidBody->setLinearVelocity(Vector2{});
    _ticksToLive = 0;
}
