//
// Created by jaaps on 02/11/2022.
//

#ifndef GOLFENGINE_PARTICLESYSTEM_H
#define GOLFENGINE_PARTICLESYSTEM_H

#include "Component.h"
#include "Drawable.h"
#include "SpriteComponent.h"


class ParticleSystem : public Component, public Drawable{
public:
    ParticleSystem(const std::string &spritePath, int particlesPerSecond, float duration, Vector2 pixelScale);

    void play(bool looping);
    void stop();
    // Drawable override
    RenderShape& getRenderShape() override;


    // Component overrides
    void onStart() override;
    void onUpdate() override;
    void onRemove() override;
    bool getActive() override;
    void setActive(bool active) override;
    void setParentGameObject(GameObject& gameObject) override;

private:
    bool _looping;
    int _particlesPerSecond;
    float _duration;
    std::string _spritePath;

    int _countedFrames;
    int _counterFromesForParticles;

    SpriteRenderShape _renderShape;
};


#endif //GOLFENGINE_PARTICLESYSTEM_H
