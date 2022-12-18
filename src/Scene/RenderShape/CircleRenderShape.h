//
// Created by conner on 11/2/2022.
//

#ifndef SPC_PROJECT_CIRCLERENDERSHAPE_H
#define SPC_PROJECT_CIRCLERENDERSHAPE_H

#include "RenderShape.h"
#include "../Vector2.h"
#include "../Color.h"

class CircleRenderShape : public RenderShape{
public:
    /// RenderShape used to render a circle
    /// \param position position of circle
    /// \param radius radius of circle
    /// \param color color of circle
    CircleRenderShape(Vector2 position, float radius, Color color);
    RenderShapeType getType() override;
    void applyTransform(const Transform& transform) override;

    //getters
    [[nodiscard]] Vector2 position() const;
    [[nodiscard]] float radius() const;
    [[nodiscard]] Color color() const;


private:
    Vector2 _initialPosition;
    float _initialRadius;

    Vector2 _position;
    float _radius;
    Color _color;
};


#endif //SPC_PROJECT_CIRCLERENDERSHAPE_H
