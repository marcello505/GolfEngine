//
// Created by jaaps on 02/11/2022.
//

#ifndef GOLFENGINE_BOXCOLLIDER_H
#define GOLFENGINE_BOXCOLLIDER_H
#include "../Vector2.h"
#include "Collider.h"

class BoxCollider : public Collider {
public:
    explicit BoxCollider(const Vector2& vec2) : _shapeExtents{vec2} {};
    void onStart() override;
    void onUpdate() override;
    void onRemove() override;
    ColliderShapes getColliderShape() override;
    const Vector2& getShapeExtents() const;

private:
    Vector2 _shapeExtents;
};


#endif //GOLFENGINE_BOXCOLLIDER_H
