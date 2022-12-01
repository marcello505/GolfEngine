//
// Created by marcello on 12/1/22.
//

#include "ProjectileScript.h"

void ProjectileScript::onStart() {
    _rigidBody = &_gameObject.value().get().getComponent<RigidBody>();
}

void ProjectileScript::onUpdate() {
    _rigidBody->applyForceToCenter({10.0f, 0.0f});
    if(_ttl < 5.0f){
    }
}

void ProjectileScript::shoot(const Transform& transform) {
    _rigidBody->setActive(true);
    _rigidBody->setTransform(transform);
    _ttl = 0.0f;
}
