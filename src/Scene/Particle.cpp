//
// Created by Lucas on 28-11-2022.
//

#include "Particle.h"

namespace GolfEngine::Scene {
    Particle::Particle(std::string path, float velocity, float rotation, Vector2 pixelScale, Color color) : lifeTime{0},
                                                                                                            _velocity{
                                                                                                                    velocity},
                                                                                                            _renderShape(
                                                                                                                    path,
                                                                                                                    Vector2(),
                                                                                                                    rotation,
                                                                                                                    pixelScale,
                                                                                                                    Rect2(),
                                                                                                                    Vector2(),
                                                                                                                    color) {
    }

    Render::RenderShape &Particle::getRenderShape() {
        return _renderShape;
    }

    Render::SpriteRenderShape &Particle::getSpriteRenderShape() {
        return _renderShape;
    }

    void Particle::setRadian(float radian) {
        _radian = radian;
    }

    float Particle::getRadian() const {
        return _radian;
    }

    void Particle::setVelocity(float velocity) {
        _velocity = velocity;
    }

    float Particle::getVelocity() const {
        return _velocity;
    }
}
