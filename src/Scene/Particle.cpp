//
// Created by Lucas on 28-11-2022.
//

#include "Particle.h"

Particle::Particle(std::string path, Vector2 pixelScale) : lifeTime{0},
_renderShape(path, Vector2(0,0), 0, pixelScale, Rect2(), Vector2() , Color())
{
}

RenderShape& Particle::getRenderShape() {
    return _renderShape;
}

SpriteRenderShape& Particle::getSpriteRenderShape() {
    return _renderShape;
}