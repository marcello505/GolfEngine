//
// Created by conner on 11/2/2022.
//

#ifndef SPC_PROJECT_RECTRENDERSHAPE_H
#define SPC_PROJECT_RECTRENDERSHAPE_H

#include "RenderShape.h"
#include "../Rect2.h"
#include "../Color.h"

class RectRenderShape : public RenderShape {
public:
    explicit RectRenderShape(Rect2 rect, float rotation = 0, Color color = Color(255,255,255));
    RenderShapeType getType() override;
    void applyTransform(const Transform& transform) override;

    // Getters
    [[nodiscard]] Rect2 rect() const;
    [[nodiscard]] float rotation() const;
    [[nodiscard]] Color color() const;
private:
    Rect2 _rect;
    Vector2 _initialSize;
    float _rotation;
    Color _color;
};


#endif //SPC_PROJECT_RECTRENDERSHAPE_H
