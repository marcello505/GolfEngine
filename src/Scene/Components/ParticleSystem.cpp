//
// Created by jaaps on 02/11/2022.
//

#include "ParticleSystem.h"
#include "Utilities/Math.h"
#include "Utilities/Random.h"

#include <cmath>
#include "Services/Singletons/RenderSingleton.h"
#include "Services/Singletons/PhysicsSingleton.h"

namespace GolfEngine::Scene::Components {
    ParticleSystem::ParticleSystem(const std::string &spritePath, int particlesPerSecond, float lifeTime,
                                   Vector2 pixelScale, Vector2 position, float rotation, Color color) :
            _position{position}, _rotation{rotation}, _color{color},
            _spritePath{spritePath}, _particlesPerSecond{particlesPerSecond}, _lifeTime{lifeTime},
            _pixelScale{pixelScale} {
    }

    Particle &ParticleSystem::addParticle() {
        int randomRotation = 0;
        if (_randomStartRotation) {
            randomRotation = GolfEngine::Utilities::Random::getIntRange(0, 359);
        }
        particles.push_back(
                std::make_unique<Particle>(_spritePath, _velocity, _randomStartRotation ? randomRotation : _rotation,
                                           _pixelScale, _color));
        auto &particle = particles.at(particles.size() - 1);

        auto transform = _gameObject->get().getWorldTransform();
        transform.rotation += particle->getSpriteRenderShape().rotation();

        transform.position.x += _position.x;
        transform.position.y += _position.y;

        particle->getSpriteRenderShape().applyTransform(transform);
        if (_spread.y != 0) {
            float degree = GolfEngine::Utilities::Random::getRealRange(std::abs(_spread.x), std::abs(_spread.y));
            particle.get()->setRadian(GolfEngine::Utilities::Math::deg2Rad(degree));
        }

        if (_randomVelocity.x != 0 || _randomVelocity.y != 0) {
            float velocity = GolfEngine::Utilities::Random::getRealRange(_randomVelocity.x, _randomVelocity.y);
            particle->setVelocity(velocity);
        }

        return *particle;
    }

    void ParticleSystem::play(bool looping) {
        _looping = looping;

        // If not looping shoot all particles as a one shot
        if (!_looping) {
            for (int i = 0; i < _particlesPerSecond; i++) {
                auto &particle = addParticle();
                if (GolfEngine::Services::Render::hasService())
                    GolfEngine::Services::Render::getService()->addDrawable(particle);
            }
        } else {
            auto &particle = addParticle();
            if (GolfEngine::Services::Render::hasService())
                GolfEngine::Services::Render::getService()->addDrawable(particle);
        }
    }

    void ParticleSystem::stop() {
        _looping = false;
    }

    void ParticleSystem::onUpdate() {
        _countedFrames++;
        // update all particles lifeTimes
        for (auto &particle: particles) {
            particle->lifeTime++;
        }

        //checks if any particle->lifteime is longer then duration then auto removes this particle
        auto it = std::find_if(particles.begin(), particles.end(),
                               [this](auto &p) { return p->lifeTime > _fps * _lifeTime; });
        if (it != particles.end()) {
            auto renderService = GolfEngine::Services::Render::getService();
            if (renderService)
                renderService->removeDrawable(*(*it));
            particles.erase(it);
        }

        // creates a new particle
        if (_looping && _countedFrames > _fps / _particlesPerSecond) {
            auto &particle = addParticle();
            auto renderService = GolfEngine::Services::Render::getService();
            if (renderService)
                renderService->addDrawable(particle);

            _countedFrames = 0;
        }

        // Repositions all particles
        for (auto &particle: particles) {
            auto t = Transform(particle->getSpriteRenderShape().position(), particle->getSpriteRenderShape().rotation(),
                               particle->getSpriteRenderShape().pixelScale());
            if (particle->getRadian() != 0) {
                t.position.x += std::cos(particle->getRadian()) * particle->getVelocity();
                t.position.y += std::sin(particle->getRadian()) * particle->getVelocity();;
            } else {
                t.position.x += _direction.x * particle->getVelocity();;
                t.position.y += _direction.y * particle->getVelocity();;
            }
            if (_fade) {
                //gets color value
                auto c = particle->getSpriteRenderShape().color();

                //Calculation to calculate how far the opacity should be decreased to be at zero when particles ends.
                int downStep = c.a / ((_fps * _lifeTime) - particle->lifeTime);
                c.a -= downStep;
                particle->getSpriteRenderShape().setColor(c);
            }
            if (_rotationsPerSecond != 0) {
                auto rotateByDegrees = 360 / (_fps / _rotationsPerSecond);
                t.rotation += rotateByDegrees;
            }

            t.scale = {1, 1};
            particle->getSpriteRenderShape().applyTransform(t);
        }
    }

    void ParticleSystem::onRemove() {
        //Delete all particles
        for (auto &particle: particles) {
            auto renderService = GolfEngine::Services::Render::getService();
            if (renderService && renderService->isRegistered(*particle))
                renderService->removeDrawable(*particle);
        }
    }

    bool ParticleSystem::getActive() {
        return _active;
    }

    void ParticleSystem::setActive(bool active) {
        _active = active;
    }

    void ParticleSystem::setParentGameObject(GameObject &gameObject) {
        _gameObject = gameObject;
    }

    void ParticleSystem::setVelocity(float velocity) {
        _velocity = velocity;
    }

    void ParticleSystem::setDirection(Vector2 direction) {
        _direction = direction;
    }

    void ParticleSystem::setSpread(Vector2 spread) {
        _spread = spread;
    }

    void ParticleSystem::setFade(bool fade) {
        _fade = fade;
    }

    void ParticleSystem::setRotationsPerSecond(float rotationsPerSecond) {
        _rotationsPerSecond = rotationsPerSecond;
    }

    void ParticleSystem::setRandomVelocity(Vector2 randomVelocity) {
        _randomVelocity = randomVelocity;
    }

    std::unique_ptr<ISnapshot> ParticleSystem::saveSnapshot() {
        //Empty on purpose
        return {};
    }

    void ParticleSystem::loadSnapshot(const ISnapshot &rawSnapshot) {
        //Empty on purpose
    }

    void ParticleSystem::setRandomStartRotation(bool randomRotation) {
        _randomStartRotation = randomRotation;
    }

    void ParticleSystem::onStart() {}
}
