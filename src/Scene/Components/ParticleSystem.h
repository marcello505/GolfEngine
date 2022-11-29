//
// Created by jaaps on 02/11/2022.
//

#ifndef GOLFENGINE_PARTICLESYSTEM_H
#define GOLFENGINE_PARTICLESYSTEM_H

#include <random>
#include "Component.h"
#include "Drawable.h"
#include "SpriteComponent.h"
#include "Scene/Particle.h"


class ParticleSystem : public Component{
public:
    ParticleSystem(const std::string &spritePath, int particlesPerSecond, float duration, Vector2 pixelScale = Vector2(),
                   Vector2 position = Vector2(), float rotation = 0, Color color = Color());

    void play(bool looping);
    void stop();


    // Component overrides
    void onStart() override;
    void onUpdate() override;
    void onRemove() override;
    bool getActive() override;
    void setActive(bool active) override;
    void setParentGameObject(GameObject& gameObject) override;

//    setters
    void setVelocity(float velocity);
    void setDirection(Vector2 direction);
    void setSpread(Vector2 spread);
    void setFade(bool fade);
    void setRotationsPerSecond(float rotationsPerSecond);


private:
    Particle& addParticle();


    std::vector<std::unique_ptr<Particle>> particles {};


    int _particlesPerSecond;
    float _duration;
    std::string _spritePath;
    Vector2 _pixelScale;

    float _rotation;
    Vector2 _position;
    Color _color;


    int _countedFrames {0};

    Vector2 _direction {1,0};
    float _velocity {1.0};
    Vector2 _spread {0,0};
    bool _fade {false};
    bool _looping {false};
    float _rotationsPerSecond {0};


    std::unique_ptr<std::default_random_engine> _randomEngine;

    int _fps;
};


#endif //GOLFENGINE_PARTICLESYSTEM_H
