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

void BoxCollider::setParentGameObject(GameObject& gameObject) {
    _gameObject = std::make_unique<std::reference_wrapper<GameObject>>(gameObject);
}

RenderShape* BoxCollider::getRenderShape() {
    if(_gameObject != nullptr){
        _rectRenderShape.applyTransform(_gameObject->get().getWorldTransform());
    }
    return &_rectRenderShape;
}
