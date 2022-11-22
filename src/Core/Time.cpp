//
// Created by marcello on 11/7/22.
//

#include "Time.h"

GameTic GolfEngine::Time::getPhysicsDeltaTime() const {
    return _physicsDeltaTime;
}

GameTic GolfEngine::Time::getRenderDeltaTime() const {
    return _renderDeltaTime;
}

void GolfEngine::Time::measurePhysicsCall() {
    //TODO find a way to shield this against misuse (this should only be called by GameLoop)
    auto current = std::chrono::steady_clock::now();
    std::chrono::duration<GameTic, std::milli> elapsed = current - _previousPhysicsCall;
    _previousPhysicsCall = current;
    _physicsFpsCounter += elapsed;
    _physicsCalls++;
    _physicsDeltaTime = elapsed.count() / 1000.f;

    if(_physicsFpsCounter >= _interval){
        _fpsPhysics = (1000.f / _interval.count()) * (GameTic)_physicsCalls;
        _physicsCalls = 0;
        _physicsFpsCounter -= _interval;
    }
}

void GolfEngine::Time::measureRenderCall() {
    //TODO find a way to shield this against misuse (this should only be called by GameLoop)
    auto current = std::chrono::steady_clock::now();
    std::chrono::duration<GameTic, std::milli> elapsed = current - _previousRenderCall;
    _previousRenderCall = current;
    _renderFpsCounter += elapsed;
    _renderCalls++;
    _renderDeltaTime = elapsed.count() / 1000.f;

    if(_renderFpsCounter >= _interval){
        _fpsRender = (1000.f / _interval.count()) * (GameTic)_renderCalls;
        _renderCalls = 0;
        _renderFpsCounter -= _interval;
    }
}

GameTic GolfEngine::Time::getPhysicsFps() const {
    return _fpsPhysics;
}

GameTic GolfEngine::Time::getRenderFps() const {
    return _fpsRender;
}

GameTic GolfEngine::Time::getTimeScale() const {
    return _timeScale;
}

void GolfEngine::Time::setTimeScale(GameTic timeScale) {
    _timeScale = timeScale;
}