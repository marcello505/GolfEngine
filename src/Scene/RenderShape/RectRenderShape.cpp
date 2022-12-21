//
// Created by conner on 11/2/2022.
//

#include "RectRenderShape.h"

namespace GolfEngine::Scene::Render {
    RectRenderShape::RectRenderShape(Rect2 rect, float rotation, Vector2 pivotPoint, Color color)
            : _rect{rect}, _initialPosition{rect.position}, _rotation{rotation}, _color{color}, _initialSize{rect.size},
              _pivotPoint{pivotPoint}, _initialPivotPoint{pivotPoint} {
    }

    RenderShapeType RectRenderShape::getType() {
        return RenderShapeType::RectShape;
    }

    Rect2 RectRenderShape::rect() const {
        return _rect;
    }

    float RectRenderShape::rotation() const {
        return _rotation;
    }

    Color RectRenderShape::color() const {
        return _color;
    }

    void RectRenderShape::applyTransform(const Transform &transform) {
        _rect.position.x = _initialPosition.x + transform.position.x;
        _rect.position.y = _initialPosition.y + transform.position.y;
        _rotation = transform.rotation;
        _rect.size.x = _initialSize.x * transform.scale.x;
        _rect.size.y = _initialSize.y * transform.scale.y;
        _pivotPoint.x = _initialPivotPoint.x * transform.scale.x;
        _pivotPoint.y = _initialPivotPoint.y * transform.scale.y;
    }

    Vector2 RectRenderShape::pivotPoint() const {
        return _pivotPoint;
    }

    void RectRenderShape::setColor(Color color) {
        _color = color;
    }
}
