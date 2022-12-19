//
// Created by Lucas on 2-11-2022.
//

#include <chrono>
#include "GameLoop.h"
#include "../Services/SDLAudioService.h"
#include "../Services/SDLInputService.h"
#include "../Services/SDLRenderService.h"
#include "../Services/Box2DPhysicsService.h"
#include "../Services/PugiXMLTileMapParserService.h"
#include "../Services/AStarPathfindingService.h"
#define GOLFENGINE_SINGLETON_PRIVATE //Grants access to the "private" methods of singletons
#include "../Services/Singletons/PhysicsSingleton.h"
#include "../Services/Singletons/AudioSingleton.h"
#include "../Services/Singletons/RenderSingleton.h"
#include "../Services/Singletons/InputSingleton.h"
#include "../Services/Singletons/PathfindingSingleton.h"
#include "../Services/Singletons/TileMapParserSingleton.h"
#include "../Input/ActionMap.h"

using namespace GolfEngine::Services;

namespace GolfEngine::Core {
    GameLoop *_currentlyRunningGameLoop{};

    GameLoop &getRunningGameLoop() {
        if (_currentlyRunningGameLoop) {
            return *_currentlyRunningGameLoop;
        } else {
            throw std::logic_error("No GameLoop is currently running.");
        }
    }

    bool hasRunningGameLoop() {
        return _currentlyRunningGameLoop != nullptr;
    }


    void GameLoop::start() {
        //Set this GameLoop as the currently running GameLoop
        _currentlyRunningGameLoop = this;

        //Initialize services
        if (Audio::hasService()) Audio::getService()->init();

        _previous = std::chrono::steady_clock::now();
        std::chrono::duration<GameTic, std::milli> lag{0.0f};

        while (_running) {
            auto current = std::chrono::steady_clock::now();
            auto elapsed = current - _previous;
            _previous = current;
            lag += elapsed;

            processInput();

            while (lag >= _msPerUpdate / time->getTimeScale()) {
                update();
                findPaths();
                lag -= _msPerUpdate / time->getTimeScale();
            }

            render();
        }
    }

    void GameLoop::stop() {
        _currentlyRunningGameLoop = nullptr;
        _running = false;
    }

    void GameLoop::processInput() {
        if (Services::Input::hasService()) {
            Services::Input::getService()->handleInputs();
            _running &= !Services::Input::getService()->hasReceivedQuitSignal();
        }
    }

    void GameLoop::update() {
        time->measurePhysicsCall();

        if (Physics::hasService()) {
            Physics::getService()->update(_msPerUpdate.count() / 1000.0f);
        }

        // Update scene
        auto &sceneManager = SceneManager::GetSceneManager();
        sceneManager.updateSceneManager();
        if (sceneManager.hasCurrentScene()) {
            auto &currentScene = sceneManager.getCurrentScene();
            currentScene.updateReplay();
            currentScene.updateScene();
        }

        if (ActionMap::getActionMap()) {
            ActionMap::getActionMap()->update();
        }
    }

    void GameLoop::render() {
        time->measureRenderCall();

        if (Services::Render::hasService()) {
            Services::Render::getService()->render();
        }
    }

    void GameLoop::findPaths() {
        if (Services::Pathfinding::hasService()) {
            Services::Pathfinding::getService()->findPathEveryTick();
        }
    }

    void GameLoop::useDefaultServices() {
        setInputService(new Services::Input::SDLInputService());
        setAudioService(new Services::Audio::SDLAudioService());
        setRenderService(new Services::Render::SDLRenderService{});
        setPhysicsService(new Services::Physics::Box2DPhysicsService{});
        setTileMapParserService(new Services::TileMapParser::PugiXMLTileMapParserService{});
        setPathfindingService(new Services::Pathfinding::AStarPathfindingService{});
    }

// SETTERS AND GETTERS
    void GameLoop::setFramesPerSeccond(GameTic fps) {
        _msPerUpdate = std::chrono::duration<GameTic, std::milli>{1000.f / fps};
    }

    void GameLoop::setAudioService(Audio::AudioService *audioService) {
        if (Audio::hasService()) {
            Audio::getService()->free();
        }

        if (audioService)
            audioService->init();
        Audio::setService(audioService);
    }

    void GameLoop::setInputService(Services::Input::InputService *inputService) {
        Services::Input::setService(inputService);
    }

    void GameLoop::setRenderService(Services::Render::RenderService *renderService) {
        Services::Render::setService(renderService);
    }

    void GameLoop::setPhysicsService(Services::Physics::PhysicsService *physicsService) {
        Physics::setService(physicsService);
    }

    void GameLoop::setTileMapParserService(Services::TileMapParser::TileMapParserService *tileMapParserService) {
        TileMapParser::setService(tileMapParserService);
    }

    void GameLoop::setPathfindingService(Services::Pathfinding::PathfindingService *pathfindingService) {
        Services::Pathfinding::setService(pathfindingService);
    }

    bool GameLoop::isGameRunning() const {
        return _running;
    }

    void GameLoop::resetLag() {
        _previous = std::chrono::steady_clock::now();
    }
}
