//
// Created by Lucas on 28-11-2022.
//

#ifndef GOLFENGINE_PARTICLE_H
#define GOLFENGINE_PARTICLE_H

#include "Scene/Components/Drawable.h"
#include "Scene/RenderShape/SpriteRenderShape.h"

class Particle : public Drawable {
public:
    /// Particle object managed by ParticleSystem component
    /// \param path sprite path
    /// \param velocity velocity of particle
    /// \param rotation rotation of particle
    /// \param pixelScale initial pixel scale of particle
    /// \param color color to blend with sprite image
    Particle(std::string path, float velocity, float rotation, Vector2 pixelScale, Color color);

    // Drawable override
    RenderShape& getRenderShape() override;
    SpriteRenderShape &getSpriteRenderShape();

    //getters
    [[nodiscard]] float getRadian() const;
    [[nodiscard]] float getVelocity() const;

    //setters
    void setRadian(float radian);
    void setVelocity(float velocity);

    int lifeTime {0};
private:
    SpriteRenderShape _renderShape;
    float _radian {0};
    float _velocity{1};

};
#endif //GOLFENGINE_PARTICLE_H
