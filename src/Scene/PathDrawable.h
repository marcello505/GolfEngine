//
// Created by Lucas on 12-12-2022.
//

#ifndef GOLFENGINE_PATHDRAWABLE_H
#define GOLFENGINE_PATHDRAWABLE_H


#include "Scene/Components/Drawable.h"
#include "Scene/RenderShape/RectRenderShape.h"

class PathDrawable : public Drawable{
public:
    explicit PathDrawable(Rect2 rect, Color color = Color());
    RenderShape& getRenderShape() override;
    void setColor(Color color);

private:
    RectRenderShape _renderShape;
    Transform _transform;

};


#endif //GOLFENGINE_PATHDRAWABLE_H
