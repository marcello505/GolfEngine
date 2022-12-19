//
// Created by conner on 11/2/2022.
//

#ifndef SPC_PROJECT_LINERENDERSHAPE_H
#define SPC_PROJECT_LINERENDERSHAPE_H

#include "RenderShape.h"
#include "../Vector2.h"
#include "../Color.h"

namespace GolfEngine::Scene::Render {
    class LineRenderShape : public RenderShape {
    public:
        /// RenderShape used to render a line
        /// \param posA first position of line
        /// \param posB second position of line
        /// \param color color of line
        LineRenderShape(Vector2 posA, Vector2 posB, Color color = Color(255, 255, 255));
        RenderShapeType getType() override;
        void applyTransform(const Transform &transform) override;

        // Getter
        [[nodiscard]] Vector2 positionA() const;
        [[nodiscard]] Vector2 positionB() const;
        [[nodiscard]] Color color() const;

    private:
        Vector2 _positionA;
        Vector2 _positionB;
        Color _color;
    };
}


#endif //SPC_PROJECT_LINERENDERSHAPE_H
