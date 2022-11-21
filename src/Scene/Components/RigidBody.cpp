#include "../../Services/Singletons/PhysicsSingleton.h"
#include "RigidBody.h"
#include "BoxCollider.h"
#include "CircleCollider.h"

void RigidBody::onStart() {
    if(GolfEngine::Services::Physics::hasService()){
        GolfEngine::Services::Physics::getService()->addRigidBody(this);
    }
}

void RigidBody::onUpdate() {

}

void RigidBody::onRemove() {
    if(GolfEngine::Services::Physics::hasService()){
        GolfEngine::Services::Physics::getService()->removeRigidBody(this);
    }
}

const RigidBodyDef& RigidBody::getRigidBodyDef() const {
    return _rigidBodyDef;
}

std::vector<Collider*> RigidBody::getColliders() const {
    std::vector<Collider*> result {};
    if(_parent != nullptr){
        //TODO make this so that multiple instances of the same type work?
        auto* pBoxCollider = _parent->getComponent<BoxCollider>();
        auto* pCircleCollider = _parent->getComponent<CircleCollider>();

        if(pBoxCollider != nullptr) result.push_back(pBoxCollider);
        if(pCircleCollider != nullptr) result.push_back(pCircleCollider);
    }


    return result;
}

bool RigidBody::getActive() {
    return _active;
}

void RigidBody::setActive(bool active) {
    _active = active;
    if(GolfEngine::Services::Physics::hasService()){
        GolfEngine::Services::Physics::getService()->setEnabled(this, active);
    }
}

void RigidBody::setParentGameObject(GameObject* gameObject) {
    _parent = gameObject;
}

Component* RigidBody::clone() const {
    return new RigidBody{*this};
}

GameObject* RigidBody::getParentGameObject() const {
    return _parent;
}

void RigidBody::applyForceToCenter(const Vector2& force) {
    if(GolfEngine::Services::Physics::hasService()){
        GolfEngine::Services::Physics::getService()->applyForceToCenter(this, force);
    }
}

void RigidBody::setTransform(const Transform& transform) {
    if(GolfEngine::Services::Physics::hasService()){
        GolfEngine::Services::Physics::getService()->setTransform(this, transform);
    }
}

void RigidBody::setLinearDamping(float linearDamping) {
    if(GolfEngine::Services::Physics::hasService()){
        GolfEngine::Services::Physics::getService()->setLinearDamping(this, linearDamping);
    }
}

void RigidBody::setAngularDamping(float angularDamping) {
    if(GolfEngine::Services::Physics::hasService()){
        GolfEngine::Services::Physics::getService()->setAngularDamping(this, angularDamping);
    }
}

void RigidBody::setFixedRotation(bool fixedRotation) {
    if(GolfEngine::Services::Physics::hasService()){
        GolfEngine::Services::Physics::getService()->setFixedRotation(this, fixedRotation);
    }
}

void RigidBody::setGravityScale(float gravityScale) {
    if(GolfEngine::Services::Physics::hasService()){
        GolfEngine::Services::Physics::getService()->setGravityScale(this, gravityScale);
    }
}