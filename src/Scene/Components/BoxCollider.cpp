//
// Created by marcello on 11/14/22.
//

#include "BoxCollider.h"

void BoxCollider::onStart() {

}

void BoxCollider::onUpdate() {

}

void BoxCollider::onRemove() {

}

ColliderShapes BoxCollider::getColliderShape() {
    return ColliderShapes::Box;
}

const Vector2& BoxCollider::getShapeExtents() const {
    return _shapeExtents;
}

bool BoxCollider::getActive() {
    return false;
}

void BoxCollider::setActive(bool active) {

}

void BoxCollider::setParentGameObject(GameObject* gameObject) {
    _parent = gameObject;
}

Component* BoxCollider::clone() const {
    return nullptr;
}

RenderShape* BoxCollider::getRenderShape() {
    return nullptr;
}
