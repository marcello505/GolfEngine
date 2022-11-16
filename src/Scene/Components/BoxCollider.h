//
// Created by jaaps on 02/11/2022.
//

#ifndef GOLFENGINE_BOXCOLLIDER_H
#define GOLFENGINE_BOXCOLLIDER_H
#include "../Vector2.h"
#include "../RenderShape/RectRenderShape.h"
#include "Collider.h"

class BoxCollider : public Collider {
public:
    //TODO make the _rectRenderShape initialisation more natural
    explicit BoxCollider(const Vector2& vec2) : _shapeExtents{vec2}, _rectRenderShape{{{}, {vec2.x * 2, vec2.y * 2}}} {};
    ColliderShapes getColliderShape() override;
    const Vector2& getShapeExtents() const;

    // Component overrides
    void onStart() override;
    void onUpdate() override;
    void onRemove() override;
    Component* clone() const override;
    bool getActive() override;
    void setActive(bool active) override;
    void setParentGameObject(GameObject* gameObject) override;

    //Drawable overrides
    RenderShape* getRenderShape() override;

private:
    GameObject* _parent {};
    RectRenderShape _rectRenderShape;
    Vector2 _shapeExtents;
};


#endif //GOLFENGINE_BOXCOLLIDER_H
