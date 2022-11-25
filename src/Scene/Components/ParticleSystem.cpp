//
// Created by jaaps on 02/11/2022.
//

#include "ParticleSystem.h"
#include "Services/Singletons/RenderSingleton.h"
#include "Services/Singletons/PhysicsSingleton.h"

ParticleSystem::ParticleSystem(const std::string &spritePath, int particlesPerSecond, float duration, Vector2 pixelScale):
_spritePath{spritePath}, _particlesPerSecond{particlesPerSecond}, _duration{duration},
_renderShape(spritePath, Vector2(), 0, pixelScale, Rect2(), Vector2() , Color())
{
}
void ParticleSystem::play(bool looping) {
    auto renderService = GolfEngine::Services::Render::getService();
    if(renderService)
        renderService->addDrawable(*this);
}
void ParticleSystem::stop() {
    auto renderService = GolfEngine::Services::Render::getService();
    if(renderService)
        renderService->removeDrawable(*this);
}

void ParticleSystem::onStart() {
    if(_gameObject){
        _renderShape.applyTransform(_gameObject->get().getWorldTransform());
    }
}

void ParticleSystem::onUpdate() {
    _countedFrames ++;
    _counterFromesForParticles ++;
    if(_countedFrames > 60 * _duration) {
        _countedFrames = 0;
        stop();
    }else if(_counterFromesForParticles > 60/_particlesPerSecond){
       auto  t = Transform(_renderShape.position(), _renderShape.rotation(), _renderShape.pixelScale());


       t.position.x += 10;
       t.scale = {1,1};
        _renderShape.applyTransform(t);
        _counterFromesForParticles = 0;
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

RenderShape& ParticleSystem::getRenderShape() {
    return _renderShape;
}



