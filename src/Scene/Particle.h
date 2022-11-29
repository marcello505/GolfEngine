//
// Created by Lucas on 28-11-2022.
//

#ifndef GOLFENGINE_PARTICLE_H
#define GOLFENGINE_PARTICLE_H

#include "Scene/Components/Drawable.h"
#include "Scene/RenderShape/SpriteRenderShape.h"

class Particle : public Drawable {
public:
    Particle(std::string path, float rotation, Vector2 pixelScale, Color color);


    // Drawable override
    RenderShape& getRenderShape() override;

    SpriteRenderShape &getSpriteRenderShape();

    //getters
    float getRadian() const;

    //setters
    void setRadian(float radian);

    int lifeTime {0};


private:
    SpriteRenderShape _renderShape;
    float _radian {0};

};
#endif //GOLFENGINE_PARTICLE_H
