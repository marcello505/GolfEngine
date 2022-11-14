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