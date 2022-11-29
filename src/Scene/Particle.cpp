//
// Created by Lucas on 28-11-2022.
//

#include "Particle.h"

Particle::Particle(std::string path, float rotation, Vector2 pixelScale, Color color) : lifeTime{0},
_renderShape(path, Vector2(), rotation, pixelScale, Rect2(), Vector2() , color)
{
}

RenderShape& Particle::getRenderShape() {
    return _renderShape;
}

SpriteRenderShape& Particle::getSpriteRenderShape() {
    return _renderShape;
}

void Particle::setRadian(float radian) {
    _radian = radian;
}

float Particle::getRadian() const {
    return _radian;
}

