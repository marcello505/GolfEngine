//
// Created by jaaps on 02/11/2022.
//

#include "ParticleSystem.h"
#include "Services/Singletons/RenderSingleton.h"
#include "Services/Singletons/PhysicsSingleton.h"

//Duration is time until one particle goes away
// pps = how many particles to render every second if looping == true

ParticleSystem::ParticleSystem(const std::string &spritePath, int particlesPerSecond, float duration, Vector2 pixelScale):
_spritePath{spritePath}, _particlesPerSecond{particlesPerSecond}, _duration{duration}, _pixelScale{pixelScale}, _countedFrames{0}
{
}
void ParticleSystem::play(bool looping) {
    _looping = looping;
    particles.push_back(std::make_unique<Particle>(_spritePath, _pixelScale));


    auto renderService = GolfEngine::Services::Render::getService();
    if(renderService)
        renderService->addDrawable(*particles.at(particles.size()-1));

}

void ParticleSystem::stop() {
    _looping = false;
}

void ParticleSystem::onStart() {
    if(_gameObject){
        for (auto& particle : particles) {
            auto t = _gameObject->get().getWorldTransform();
            particle->getRenderShape().applyTransform(t);
        }
    }
}

void ParticleSystem::onUpdate() {
    _countedFrames ++;
    for (auto& particle : particles) {
        particle->lifeTime++;
    }

    auto it = std::find_if(particles.begin(), particles.end(),[this](auto& p){return p->lifeTime > 60 * _duration; });
    if(it != particles.end()){
        auto renderService = GolfEngine::Services::Render::getService();
        if(renderService)
            renderService->removeDrawable(*(*it));
        particles.erase(it);
    }

     if(_countedFrames > 60/_particlesPerSecond){
        if(_looping){
            particles.push_back(std::make_unique<Particle>(_spritePath, _pixelScale));
            auto& particle = particles.at(particles.size() - 1);
            particle->getSpriteRenderShape().applyTransform(_gameObject->get().getWorldTransform());
            auto renderService = GolfEngine::Services::Render::getService();
            if(renderService){
                renderService->addDrawable(*particle);
            }


        }
        for (auto& particle : particles) {
            auto  t = Transform(particle->getSpriteRenderShape().position(), particle->getSpriteRenderShape().rotation(), particle->getSpriteRenderShape().pixelScale());
            t.position.x += 10;
            t.scale = {1,1};
            particle->getSpriteRenderShape().applyTransform(t);
        }


        _countedFrames = 0;
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





