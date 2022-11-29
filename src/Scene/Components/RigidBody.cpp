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
    if(_gameObject){
        //TODO make this so that multiple instances of the same type work?
        if(_gameObject->get().hasComponent<BoxCollider>())
            result.push_back(&_gameObject->get().getComponent<BoxCollider>());

        if(_gameObject->get().hasComponent<CircleCollider>())
            result.push_back(&_gameObject->get().getComponent<CircleCollider>());

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

void RigidBody::setParentGameObject(GameObject& gameObject) {
    _gameObject = gameObject;
}

GameObject* RigidBody::getParentGameObject() const {
    // TODO doe dit op een manier waar geen pointers gebruikt worden.
    if(_gameObject)
        return &_gameObject->get();
    else
        return nullptr;
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

Vector2 RigidBody::getLinearVelocity() {
    if(GolfEngine::Services::Physics::hasService()){
        return GolfEngine::Services::Physics::getService()->getLinearVelocity(this);
    }

    return {};
}
