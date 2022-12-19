//
// Created by conner on 11/7/2022.
//

#ifndef GOLFENGINE_RECTDRAWABLE_H
#define GOLFENGINE_RECTDRAWABLE_H

#include "Scene/Components/Drawable.h"
#include "Scene/RenderShape/RectRenderShape.h"
#include <memory>
#include "Scene/Transform.h"

using namespace GolfEngine::Scene;
using namespace GolfEngine::Scene::Render;
using namespace GolfEngine::Scene::Components;

class RectDrawable : public Drawable {
public:
    RectDrawable(Rect2 rect, Transform transform, Vector2 pivotPoint = Vector2(), Color color = Color(255,255,255));
    RenderShape& getRenderShape() override;
    void rotate(float amount);
    void scale(float amount);
    void setColor(Color color);

private:
    RectRenderShape _renderShape;
    Transform _transform;

};


#endif //GOLFENGINE_RECTDRAWABLE_H
