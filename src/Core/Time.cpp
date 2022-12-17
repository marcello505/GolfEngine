//
// Created by marcello on 11/7/22.
//

#include <algorithm>
#include "Time.h"

// Setting default timescale as 1.0
GameTic GolfEngine::Time::_timeScale {1.0f};
GameTic GolfEngine::Time::_physicsDeltaTime {0.0f};
GameTic GolfEngine::Time::_fpsPhysics {0.0f};
GameTic GolfEngine::Time::_fpsRender {0.0f};

GameTic GolfEngine::Time::getPhysicsDeltaTime() {
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

GameTic GolfEngine::Time::getPhysicsFps() {
    return _fpsPhysics;
}

GameTic GolfEngine::Time::getRenderFps() {
    return _fpsRender;
}

GameTic GolfEngine::Time::getTimeScale() {
    return _timeScale;
}

void GolfEngine::Time::setTimeScale(GameTic timeScale) {
    //Ensure that the time scale is atleast 0.1;
    _timeScale = std::max(0.1f, timeScale);
}