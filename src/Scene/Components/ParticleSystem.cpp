//
// Created by jaaps on 02/11/2022.
//

#include "ParticleSystem.h"

#include <cmath>
#include "Services/Singletons/RenderSingleton.h"
#include "Services/Singletons/PhysicsSingleton.h"

//Duration is time until one particle goes away
// pps = how many particles to render every second if looping == true

ParticleSystem::ParticleSystem(const std::string &spritePath, int particlesPerSecond, float duration, Vector2 pixelScale):
_spritePath{spritePath}, _particlesPerSecond{particlesPerSecond}, _duration{duration}, _pixelScale{pixelScale}, _countedFrames{0}
{
    //TODO if random is used at more places then create global RandomEngine that can be re-used in every class.
     std::random_device device;
    _randomEngine = std::make_unique<std::default_random_engine> (device());

}
void ParticleSystem::play(bool looping) {
    _looping = looping;

    particles.push_back(std::make_unique<Particle>(_spritePath, _pixelScale));
    auto& particle = particles.at(particles.size() - 1);
    particle->getSpriteRenderShape().applyTransform(_gameObject->get().getWorldTransform());
    auto renderService = GolfEngine::Services::Render::getService();
    if(renderService)
        renderService->addDrawable(*particle);

}

void ParticleSystem::stop() {
    _looping = false;
}

void ParticleSystem::onStart() {

}

void ParticleSystem::onUpdate() {
    _countedFrames ++;
    // update all particles lifeTimes
    for (auto& particle : particles) {
        particle->lifeTime++;
    }

    //checks if any particle->lifteime is longer then duration then auto removes this particle
    auto it = std::find_if(particles.begin(), particles.end(),[this](auto& p){return p->lifeTime > 60 * _duration; });
    if(it != particles.end()){
        auto renderService = GolfEngine::Services::Render::getService();
        if(renderService)
            renderService->removeDrawable(*(*it));
        particles.erase(it);
    }

    // creates a new particle
     if(_looping && _countedFrames > 60/_particlesPerSecond){
            particles.push_back(std::make_unique<Particle>(_spritePath, _pixelScale));
            auto& particle = particles.at(particles.size() - 1);
            particle->getSpriteRenderShape().applyTransform(_gameObject->get().getWorldTransform());
            if(_spread.y != 0){
                std::uniform_int_distribution<int> dist {abs(_spread.x), abs(_spread.y)};

                int degree = dist(*_randomEngine);
                particle.get()->setRadian((M_PI * degree) / 180);

            }


            auto renderService = GolfEngine::Services::Render::getService();
            if(renderService)
                renderService->addDrawable(*particle);

            _countedFrames = 0;

     }

    // Repositions all particles
    for (auto& particle : particles) {
        auto  t = Transform(particle->getSpriteRenderShape().position(), particle->getSpriteRenderShape().rotation(), particle->getSpriteRenderShape().pixelScale());
        if(particle->getRadian() != 0){
            t.position.x += std::cos(particle->getRadian()) * _velocity;
            t.position.y += std::sin(particle->getRadian()) * _velocity;
        }
        else {
            t.position.x += _direction.x * _velocity;
            t.position.y += _direction.y * _velocity;
        }
        if(_fade){
            //gets color value
            auto c = particle->getSpriteRenderShape().color();

            //Calculation to calculate how far the opacity should be decreased to be at zero when particles ends.
            int downstep = c.a / (( 60 * _duration) -particle->lifeTime);
            c.a -= downstep;
            particle->getSpriteRenderShape().setColor(c);
        }
        t.scale = {1,1};
        particle->getSpriteRenderShape().applyTransform(t);

    }

}

void ParticleSystem::onRemove() {

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
