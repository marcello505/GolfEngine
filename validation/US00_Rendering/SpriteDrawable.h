//
// Created by conner on 11/9/2022.
//

#ifndef GOLFENGINE_SPRITEDRAWABLE_H
#define GOLFENGINE_SPRITEDRAWABLE_H

#include "Scene/Components/Drawable.h"
#include "Scene/RenderShape/SpriteRenderShape.h"
#include <memory>

class SpriteDrawable : public Drawable{
public:
    SpriteDrawable(const std::string& path, Vector2 position, Vector2 pixelScale, Rect2 imageSource, Transform transform, Vector2 pivotPoint = Vector2(), Color color = Color());
    RenderShape* getRenderShape() override;
    void rotate(float amount);
    void scale(float amount);
private:
    std::unique_ptr<SpriteRenderShape> _renderShape;
    Transform _transform;
};


#endif //GOLFENGINE_SPRITEDRAWABLE_H
