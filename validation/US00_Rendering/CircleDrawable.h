//
// Created by Lucas on 15-11-2022.
//

#ifndef GOLFENGINE_CIRCLEDRAWABLE_H
#define GOLFENGINE_CIRCLEDRAWABLE_H


#include <memory>
#include "Scene/Components/Drawable.h"
#include "Scene/Color.h"
#include "Scene/RenderShape/CircleRenderShape.h"

class CircleDrawable : public Drawable {
public:

    CircleDrawable(Vector2 pos, float radius, Color color, Transform transform);

    RenderShape& getRenderShape() override;

    void scale(float scale);

    void move(int x, int y);

private:
    CircleRenderShape _renderShape;
    Transform _transform;

};


#endif //GOLFENGINE_CIRCLEDRAWABLE_H
