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
    SpriteDrawable(Rect2 rect, const std::string& path, Rect2 imageSource, Transform transform, Color color = Color(255,255,255));
    RenderShape* getRenderShape() override;
    void rotate(float amount);
private:
    std::unique_ptr<SpriteRenderShape> _renderShape;
    Transform _transform;
};


#endif //GOLFENGINE_SPRITEDRAWABLE_H
