//
// Created by conner on 11/7/2022.
//

#ifndef GOLFENGINE_LINEDRAWABLE_H
#define GOLFENGINE_LINEDRAWABLE_H

#include "Scene/Components/Drawable.h"
#include <memory>
#include "Scene/RenderShape/LineRenderShape.h"
#include "Scene/Transform.h"

using namespace GolfEngine::Scene;
using namespace GolfEngine::Scene::Render;
using namespace GolfEngine::Scene::Components;

class LineDrawable : public Drawable {
public:
    LineDrawable(Vector2 posA, Vector2 posB, Color color);
    RenderShape& getRenderShape() override;
private:
    LineRenderShape _renderShape;
    Transform _transform;
};


#endif //GOLFENGINE_LINEDRAWABLE_H
