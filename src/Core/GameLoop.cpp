//
// Created by Lucas on 2-11-2022.
//

#include <chrono>
#include "GameLoop.h"
#include "../Services/SDLAudioService.h"
#include "../Services/SDLInputService.h"
#include "../Services/SDLRenderService.h"
#include "../Services/Box2DPhysicsService.h"

void GameLoop::start() {
    auto previous = std::chrono::steady_clock::now();
    std::chrono::duration<GameTic, std::milli> lag {0.0f};

    while(_running){
        auto current = std::chrono::steady_clock::now();
        auto elapsed = current - previous;
        previous = current;
        lag += elapsed;

        processInput();

        while(lag >= _msPerUpdate){
            update();
            lag -= _msPerUpdate;
        }

        render();
    }
}

void GameLoop::stop() {
    _running = false;
}

void GameLoop::processInput() {
    if(_inputService){
        _inputService->handleInputs();
    }
}

void GameLoop::update() {
    if(_physicsService){
        _physicsService->update();
    }

    //TODO add SceneManager code
}

void GameLoop::render() {
    if(_renderService){
        _renderService->render();
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
    _audioService.reset(audioService);
}

void GameLoop::setInputService(InputService* inputService) {
    _inputService.reset(inputService);
}

void GameLoop::setRenderService(RenderService* renderService) {
    _renderService.reset(renderService);
}

void GameLoop::setPhysicsService(PhysicsService* physicsService) {
    _physicsService.reset(physicsService);
}

bool GameLoop::isGameRunning() const {
    return _running;
}
