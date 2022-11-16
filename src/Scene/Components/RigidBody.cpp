#include "../../Services/Singletons/PhysicsSingleton.h"
#include "RigidBody.h"
#include "BoxCollider.h"

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

BoxCollider tmpRigidBodyBoxCollider {{10.f, 10.f}};
std::vector<Collider*> RigidBody::getColliders() const {
    //TODO replace this with actually getting the Colliders from GameObject

    std::vector<Collider*> result {};
    result.push_back(&tmpRigidBodyBoxCollider);

    return result;
}

bool RigidBody::getActive() {
    return false;
}

void RigidBody::setActive(bool active) {

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