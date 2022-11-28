//
// Created by Lucas on 28-11-2022.
//

#ifndef GOLFENGINE_PARTICLE_H
#define GOLFENGINE_PARTICLE_H

#include "Scene/Components/Drawable.h"
#include "Scene/RenderShape/SpriteRenderShape.h"

class Particle : public Drawable {
public:
    Particle(std::string path, Vector2 pixelScale);

    // Drawable override
    RenderShape& getRenderShape() override;

    SpriteRenderShape &getSpriteRenderShape();

    int lifeTime;

private:
    SpriteRenderShape _renderShape;

};
#endif //GOLFENGINE_PARTICLE_H
