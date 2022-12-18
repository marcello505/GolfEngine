//
// Created by marcello on 12/16/22.
//

#ifndef GOLFENGINE_GRAPHRENDERSHAPE_H
#define GOLFENGINE_GRAPHRENDERSHAPE_H

#include <vector>
#include <memory>

#include "RenderShape.h"
#include "RectRenderShape.h"


class GraphRenderShape : public RenderShape {
public:
    RenderShapeType getType() override;
    void applyTransform(const Transform& transform) override;
    std::vector<std::unique_ptr<RectRenderShape>> nodes {};
};


#endif //GOLFENGINE_GRAPHRENDERSHAPE_H
