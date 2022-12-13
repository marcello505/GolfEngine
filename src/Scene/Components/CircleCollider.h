//
// Created by jaaps on 02/11/2022.
//

#ifndef GOLFENGINE_CIRCLECOLLIDER_H
#define GOLFENGINE_CIRCLECOLLIDER_H

#include <memory>

#include "Collider.h"
#include "Scene/RenderShape/CircleRenderShape.h"

class CircleCollider : public Collider{
public:
    explicit CircleCollider(float radius) : _radius{radius}, _renderShape{Vector2{}, radius, Color{}} {}

    // Methods
    float getRadius() const;

    // Override methods
    ColliderShapes getColliderShape() override;
    void onStart() override;
    void onUpdate() override;
    void onRemove() override;
    bool getActive() override;
    void setActive(bool active) override;
    void setParentGameObject(GameObject& gameObject) override;
    RenderShape& getRenderShape() override;
    std::unique_ptr<ISnapshot> saveSnapshot() override;
    void loadSnapshot(const ISnapshot& rawSnapshot) override;

private:
    bool _active {true};
    const float _radius;
    CircleRenderShape _renderShape;


};


#endif //GOLFENGINE_CIRCLECOLLIDER_H
