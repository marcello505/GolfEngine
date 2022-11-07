//
// Created by marcello on 11/7/22.
//

#include "Time.h"

GameTic GolfEngine::Time::getPhysicsDeltaTime() const {
    return _physicsDeltaTime;
}

void GolfEngine::Time::measurePhysicsCall() {
    //TODO find a way to shield this
    auto current = std::chrono::steady_clock::now();
    auto elapsed = current - _previousPhysicsCall;
    _previousPhysicsCall = current;
    _physicsFpsCounter += elapsed;
    _physicsCalls++;
    //TODO assign delta time

    if(_physicsFpsCounter >= _interval){
        _fpsPhysics = _physicsCalls * (1000 / _interval.count());
        _physicsCalls = 0;
        _physicsFpsCounter -= _interval;
    }
}

void GolfEngine::Time::measureRenderCall() {
    //TODO find a way to shield this
    auto current = std::chrono::steady_clock::now();
    auto elapsed = current - _previousRenderCall;
    _previousRenderCall = current;
    _renderFpsCounter += elapsed;
    _renderCalls++;
    //TODO assign delta time

    if(_renderFpsCounter >= _interval){
        _fpsRender = _renderCalls * (1000 / _interval.count());
        _renderCalls = 0;
        _renderFpsCounter -= _interval;
    }
}
