//
// Created by Lucas on 2-11-2022.
//

#include <chrono>
#include "GameLoop.h"
#include "../Services/SDLAudioService.h"
#include "../Services/SDLInputService.h"
#include "../Services/SDLRenderService.h"
#include "../Services/Box2DPhysicsService.h"
#define GOLFENGINE_SINGLETON_PRIVATE //Grants access to the "private" methods of singletons
#include "../Services/Singletons/PhysicsSingleton.h"
#include "../Services/Singletons/AudioSingleton.h"
#include "../Services/Singletons/RenderSingleton.h"
#include "../Services/Singletons/InputSingleton.h"

using namespace GolfEngine::Services;

void GameLoop::start() {
    auto previous = std::chrono::steady_clock::now();
    std::chrono::duration<GameTic, std::milli> lag {0.0f};

    // Create standard actions for altering the gameplay timescale
    _actionMap->addAction("decrease timescale");
    _actionMap->addAction("increase timescale");
    _actionMap->addAction("pause time");
    _actionMap->addInputKeyToAction("decrease timescale", Key_PageUp);
    _actionMap->addInputKeyToAction("increase timescale", Key_PageDown);
    _actionMap->addInputKeyToAction("pause time", Key_Home);

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
        _running &= !Input::getService()->hasRecievedQuitSignal();
    }
}

void GameLoop::update() {
    time->measurePhysicsCall();

    if(Physics::hasService()){
        Physics::getService()->update(_msPerUpdate.count() / 1000.0f);
    }

    //TODO add SceneManager code

    if(_actionMap){
        _actionMap->update();
    }
}

void GameLoop::render() {
    time->measureRenderCall();

    if(Render::hasService()){
        Render::getService()->render();
    }
}

void GameLoop::useDefaultServices() {

    setInputService(new SDLInputService{_actionMap.get()});
    setAudioService(new SDLAudioService(3));
    setRenderService(new Render::SDLRenderService {});
    setPhysicsService(new Physics::Box2DPhysicsService {});
}

// SETTERS AND GETTERS

void GameLoop::setFramesPerSeccond(GameTic fps) {
    _msPerUpdate = std::chrono::duration<GameTic, std::milli>{1000.f / fps};
}

void GameLoop::setAudioService(AudioService *audioService) {
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
