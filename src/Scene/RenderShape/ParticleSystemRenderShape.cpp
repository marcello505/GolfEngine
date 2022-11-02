//
// Created by conner on 11/2/2022.
//

#include "ParticleSystemRenderShape.h"

ParticleSystemRenderShape::ParticleSystemRenderShape() {
}

RenderShapeType ParticleSystemRenderShape::getType() {
    return RenderShapeType::ParticleSystemShape;
}

void ParticleSystemRenderShape::applyTransform(const Transform &transform) {
}
