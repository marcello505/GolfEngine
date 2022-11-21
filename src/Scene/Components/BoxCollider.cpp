//
// Created by marcello on 11/14/22.
//

#include "Services/Singletons/RenderSingleton.h"
#include "BoxCollider.h"

void BoxCollider::onStart() {
    //TODO make it so that this only happens if debug is on
    if(GolfEngine::Services::Render::hasService()){
        GolfEngine::Services::Render::getService()->addDrawable(this);
    }
}

void BoxCollider::onUpdate() {

}

void BoxCollider::onRemove() {
    if(GolfEngine::Services::Render::hasService()){
        GolfEngine::Services::Render::getService()->removeDrawable(this);
    }
}

ColliderShapes BoxCollider::getColliderShape() {
    return ColliderShapes::Box;
}

const Vector2& BoxCollider::getShapeExtents() const {
    return _shapeExtents;
}

bool BoxCollider::getActive() {
    return _active;
}

void BoxCollider::setActive(bool active) {
    _active = active;
}

void BoxCollider::setParentGameObject(GameObject* gameObject) {
    _parent = gameObject;
}

Component* BoxCollider::clone() const {
    return nullptr;
}

RenderShape* BoxCollider::getRenderShape() {
    if(_parent != nullptr){
        _rectRenderShape.applyTransform(_parent->getWorldTransform());
    }
    return &_rectRenderShape;
}
