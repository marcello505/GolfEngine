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
    /// @param rect Rect with position (center of rectangle) and initial size in pixels
    /// @param rotation Angle of rectangle in degrees
    /// @param pivotPoint Custom pivot point relative to the size given in rect parameter (size/2 = center)
    /// @param color Color used to draw the rectangle
    explicit RectRenderShape(Rect2 rect, float rotation = 0, Vector2 pivotPoint = Vector2(), Color color = Color(255,255,255));
    RenderShapeType getType() override;
    void applyTransform(const Transform& transform) override;

    // Getters
    [[nodiscard]] Rect2 rect() const;
    [[nodiscard]] float rotation() const;
    [[nodiscard]] Color color() const;
    [[nodiscard]] Vector2 pivotPoint() const;
private:
    Rect2 _rect;
    Vector2 _initialSize;
    float _rotation;
    Color _color;
    Vector2 _pivotPoint;
    Vector2 _initialPivotPoint;
};


#endif //SPC_PROJECT_RECTRENDERSHAPE_H
