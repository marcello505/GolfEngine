//
// Created by Lucas on 12-12-2022.
//

#include "PathDrawable.h"

PathDrawable::PathDrawable(Rect2 rect, Color color) : _renderShape{RectRenderShape(rect, 0, Vector2(), color)}{
}

RenderShape& PathDrawable::getRenderShape() {
    _renderShape.applyTransform(_transform);
    return _renderShape;
}
void PathDrawable::setColor(Color color){
    _renderShape.setColor(color);
}

