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

    /// starts the particles
    /// \param looping Determines if particles should be looped or only fire once.
    void play(bool looping);

    /// Stops the particles if the were looping;
    void stop();


    // Component overrides
    void onStart() override;
    void onUpdate() override;
    void onRemove() override;
    bool getActive() override;
    void setActive(bool active) override;
    void setParentGameObject(GameObject& gameObject) override;

    std::unique_ptr<ISnapshot> saveSnapshot() override;

    void loadSnapshot(const ISnapshot& rawSnapshot) override;

//    setters
    /// Sets the velocity of all particles, only works if randomVelocity is {0,0}
    /// \param velocity velocity that all particles will have
    void setVelocity(float velocity);

    /// Sets the direction of all particles, only works if spread is {0,0}
    /// \param direction direction that all particles will have
    void setDirection(Vector2 direction);

    /// Sets the spread that wil be used to calculate direction of single particle
    /// \example Vector2(60,120) each particle wil now have random direction between 60 and 120 degrees.
    /// \param spread (0-360) wil determine what min and max of the direction is
    void setSpread(Vector2 spread);

    /// Determines if particles fades, or just disappears at once.
    /// \param fade if true particles will fade.
    void setFade(bool fade);

    /// Sets the random velocity that wil be used to calculate the velocity of single particle
    /// \example Vector2(0.5,2) each particle wil now have random velocity between 0.5 and 2.
    /// \param spread wil determine what min and max of the velocity is
    void setRandomVelocity(Vector2 _randomVelocity);

    /// Determines if particles will spin.
    /// \param rotationsPerSecond the amount of rotation each particle makes every second.
    void setRotationsPerSecond(float rotationsPerSecond);


private:
    ///Creates a new particle and adds it to particles
    Particle& addParticle();

    ///List of all particles
    std::vector<std::unique_ptr<Particle>> particles {};
    bool _fade {false};
    bool _looping {false};

    int _particlesPerSecond;
    float _lifeTime;

    std::string _spritePath;
    Vector2 _pixelScale;
    float _rotation;
    Vector2 _position;
    Color _color;


    int _countedFrames {0};
    int _fps{60};


    Vector2 _direction {1,0};
    float _velocity {1.0};
    Vector2 _spread {0,0};

    Vector2 _randomVelocity {0,0};
    float _rotationsPerSecond {0};

};


#endif //GOLFENGINE_PARTICLESYSTEM_H
