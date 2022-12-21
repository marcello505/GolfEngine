//
// Created by Lucas on 15-11-2022.
//

#include "CircleDrawable.h"

CircleDrawable::CircleDrawable(Vector2 pos, float radius, Color color, Transform transform) : _transform{transform},
    _renderShape{CircleRenderShape(pos, radius, color)}{
}


RenderShape& CircleDrawable::getRenderShape() {
    _renderShape.applyTransform(_transform);
    return _renderShape;
}

void CircleDrawable::scale(float scale) {
    _transform.scale.x += scale;
    _transform.scale.y += scale;
}

void CircleDrawable::move(int x, int y) {
    _transform.position.x += x ;
    _transform.position.y += y ;
}

