//
// Created by conner on 11/2/2022.
//

#ifndef SPC_PROJECT_LINERENDERSHAPE_H
#define SPC_PROJECT_LINERENDERSHAPE_H

#include "RenderShape.h"
#include "../Vector2.h"
#include "../Color.h"

class LineRenderShape : public RenderShape {
public:
    LineRenderShape(Vector2 posA, Vector2 posB, Color color = Color(255,255,255));
    RenderShapeType getType() override;
    void applyTransform(const Transform& transform) override;

    // Getter
    [[nodiscard]] Vector2 positionA() const;
    [[nodiscard]] Vector2 positionB() const;
    [[nodiscard]] Color color() const;
private:
    Vector2 _positionA;
    Vector2 _positionB;
    Color _color;
};


#endif //SPC_PROJECT_LINERENDERSHAPE_H
