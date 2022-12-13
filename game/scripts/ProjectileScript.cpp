//
// Created by marcello on 12/1/22.
//

#include <iostream>
#include "ProjectileScript.h"

void ProjectileScript::onStart() {
    _rigidBody = &_gameObject.value().get().getComponent<RigidBody>();
    _gameObject.value().get().setActive(false);
}

void ProjectileScript::onUpdate() {
    if(_ticksToLive < 30){
        _rigidBody->setLinearVelocity(_dir * _bulletSpeed);
        _ticksToLive++;
    }
    else {
        _gameObject->get().setLocalPosition({0,0});
        _rigidBody->setTransform(_gameObject->get().getWorldTransform());
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

void ProjectileScript::onCollisionEnter(RigidBody& other) {
    if(other.getParentGameObject()->tag == "enemy")
    {
        // TODO kill the enemy
    }

    if(_ticksToLive < 30){
        _ticksToLive = 31;
    }
}