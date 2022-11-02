//
// Created by conner on 11/2/2022.
//

#ifndef SPC_PROJECT_PARTICLESYSTEMRENDERSHAPE_H
#define SPC_PROJECT_PARTICLESYSTEMRENDERSHAPE_H

#include "RenderShape.h"
#include "SpriteRenderShape.h"
#include <vector>

class ParticleSystemRenderShape : public RenderShape {
public:
    ParticleSystemRenderShape();
    RenderShapeType getType() override;
    void applyTransform(const Transform& transform) override;
private:
    std::vector<SpriteRenderShape> _particles;
    int _particleCount;
};


#endif //SPC_PROJECT_PARTICLESYSTEMRENDERSHAPE_H
