//
// Created by Lucas on 2-11-2022.
//

#include <chrono>
#include "GameLoop.h"
#include "../Services/SDLAudioService.h"
#include "../Services/SDLInputService.h"
#include "../Services/SDLRenderService.h"
#include "../Services/Box2DPhysicsService.h"
#include "../Services/Singletons/PhysicsSingleton.h"
#include "../Services/Singletons/AudioSingleton.h"
#include "../Services/Singletons/RenderSingleton.h"
#include "../Services/Singletons/InputSingleton.h"

using namespace GolfEngine::Services;

void GameLoop::start() {
    auto previous = std::chrono::steady_clock::now();
    std::chrono::duration<GameTic, std::milli> lag {0.0f};

    while(_running){
        auto current = std::chrono::steady_clock::now();
        auto elapsed = current - previous;
        previous = current;
        lag += elapsed;

        processInput();

        while(lag >= _msPerUpdate / time->getTimeScale()){
            update();
            lag -= _msPerUpdate / time->getTimeScale();
        }

        render();
    }
}

void GameLoop::stop() {
    _running = false;
}

void GameLoop::processInput() {
    if(Input::hasService()){
        Input::getService()->handleInputs();
    }
}

void GameLoop::update() {
    time->measurePhysicsCall();

    if(Physics::hasService()){
        Physics::getService()->update();
    }

    //TODO add SceneManager code

    if(_actionMap){
        //TODO update ActionMap
    }
}

void GameLoop::render() {
    time->measureRenderCall();

    if(Render::hasService()){
        Render::getService()->render();
    }
}

void GameLoop::useDefaultServices() {
    setAudioService(new SDLAudioService {});
    setInputService(new SDLInputService {});
    setRenderService(new SDLRenderService {});
    setPhysicsService(new Box2DPhysicsService {});
}

// SETTERS AND GETTERS

void GameLoop::setFramesPerSeccond(GameTic fps) {
    _msPerUpdate = std::chrono::duration<GameTic, std::milli>{1000.f / fps};
}

void GameLoop::setAudioService(AudioService* audioService) {
    Audio::setService(audioService);
}

void GameLoop::setInputService(InputService* inputService) {
    Input::setService(inputService);
}

void GameLoop::setRenderService(RenderService* renderService) {
    Render::setService(renderService);
}

void GameLoop::setPhysicsService(PhysicsService* physicsService) {
    Physics::setService(physicsService);
}

bool GameLoop::isGameRunning() const {
    return _running;
}
