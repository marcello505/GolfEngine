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
    LineRenderShape();
    RenderShapeType getType() override;
    void applyTransform(const Transform& transform) override;
private:
    Vector2 _positionA;
    Vector2 _positionB;
    Color _color;
};


#endif //SPC_PROJECT_LINERENDERSHAPE_H
