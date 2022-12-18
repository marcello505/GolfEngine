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
    /// BoxCollider is used in combination with a Rigid Body (wont do anything on its own)
    /// \param extends of box
    explicit BoxCollider(const Vector2& extends) : _shapeExtents{extends}, _rectRenderShape{{{}, {extends.x * 2, extends.y * 2}}} {};
    /// Collider shape of this collider
    /// \return collider shape based on its properties
    ColliderShapes getColliderShape() override;
    /// Get extends of this box
    /// \return extends of this box
    [[nodiscard]] const Vector2& getShapeExtents() const;

    // Component overrides
    void onStart() override;
    void onUpdate() override;
    void onRemove() override;
    bool getActive() override;
    void setActive(bool active) override;
    void setParentGameObject(GameObject& gameObject) override;

    // IPersistable overrides
    std::unique_ptr<ISnapshot> saveSnapshot() override;
    void loadSnapshot(const ISnapshot& rawSnapshot) override;

    //Drawable overrides
    RenderShape& getRenderShape() override;

    /// Set color of box collider
    /// \param color to be set
    void setColor(Color color);

private:
    bool _active {true};
    RectRenderShape _rectRenderShape;
    const Vector2 _shapeExtents;
};


#endif //GOLFENGINE_BOXCOLLIDER_H
