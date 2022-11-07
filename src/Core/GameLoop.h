//
// Created by Lucas on 2-11-2022.
//

#ifndef SPC_PROJECT_GAMELOOP_H
#define SPC_PROJECT_GAMELOOP_H

#include <memory>
#include <chrono>
#include "../Services/Abstracts/AudioService.h"
#include "../Services/Abstracts/InputService.h"
#include "../Services/Abstracts/RenderService.h"
#include "../Services/Abstracts/PhysicsService.h"
#include "SceneManager.h"
#include "../Input/ActionMap.h"
#include "Time.h"

class GameLoop {
public:
    //Getters and Setters
    void setAudioService(AudioService* audioService);
    void setInputService(InputService* inputService);
    void setRenderService(RenderService* renderService);
    void setPhysicsService(PhysicsService* physicsService);
    void setFramesPerSeccond(GameTic fps);
    [[nodiscard]] bool isGameRunning() const;

    //Methods
    void useDefaultServices();
    void start();
    void stop();

private:
    std::unique_ptr<AudioService> _audioService {};
    std::unique_ptr<InputService> _inputService {};
    std::unique_ptr<RenderService> _renderService {};
    std::unique_ptr<PhysicsService> _physicsService {};
    std::unique_ptr<SceneManager> _sceneManager = std::make_unique<SceneManager>();
    std::unique_ptr<ActionMap> _actionMap = std::make_unique<ActionMap>();
    std::unique_ptr<GolfEngine::Time> _time = std::make_unique<GolfEngine::Time>();
    bool _running {true};
    std::chrono::duration<GameTic, std::milli> _msPerUpdate {1000.f/ 60};


    void processInput();
    void update();
    void render();
};


#endif //SPC_PROJECT_GAMELOOP_H
