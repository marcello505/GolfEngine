//
// Created by conner on 11/2/2022.
//

#ifndef SPC_PROJECT_RENDERSHAPE_H
#define SPC_PROJECT_RENDERSHAPE_H

#include "RenderShapeType.h"
#include "../Transform.h"

namespace GolfEngine::Scene::Render {
    class RenderShape {
    public:
        virtual RenderShapeType getType() = 0;

        /// Applies a transform to the RenderShape properties
        /// \param transform Transform to be applied
        virtual void applyTransform(const Transform &transform) = 0;

        virtual ~RenderShape() = default;
    };
}

#endif //SPC_PROJECT_RENDERSHAPE_H
