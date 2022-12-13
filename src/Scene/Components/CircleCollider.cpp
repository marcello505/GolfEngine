#include "CircleCollider.h"
#include "Services/Singletons/RenderSingleton.h"

ColliderShapes CircleCollider::getColliderShape() {
    return ColliderShapes::Circle;
}

void CircleCollider::onStart() {
    //TODO make it so that this only happens if debug is on
    if(GolfEngine::Services::Render::hasService()){
        GolfEngine::Services::Render::getService()->addDrawable(*this);
    }
}

void CircleCollider::onUpdate() {

}

void CircleCollider::onRemove() {
    if(GolfEngine::Services::Render::hasService()){
        GolfEngine::Services::Render::getService()->removeDrawable(*this);
    }
}

bool CircleCollider::getActive() {
    return _active;
}

void CircleCollider::setActive(bool active) {
    if(_active == active) return;

    _active = active;
    if(active)
        onStart();
    else
        onRemove();
}

void CircleCollider::setParentGameObject(GameObject& gameObject) {
    _gameObject = gameObject;
}



RenderShape& CircleCollider::getRenderShape() {
    if(_gameObject){
        _renderShape.applyTransform(_gameObject->get().getWorldTransform());
    }
    return _renderShape;
}

float CircleCollider::getRadius() const {
    return _radius;
}

std::unique_ptr<ISnapshot> CircleCollider::saveSnapshot() {
    //Empty on purpose
    return {};
}

void CircleCollider::loadSnapshot(const ISnapshot& rawSnapshot) {
    //Empty on purpose
}
