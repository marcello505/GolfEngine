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
    //Fields
    std::unique_ptr<GolfEngine::Time> time = std::make_unique<GolfEngine::Time>();
    //Getters and Setters
    void setAudioService(AudioService *audioService);
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
//    std::unique_ptr<ActionMap> _actionMap = std::make_unique<ActionMap>();
    bool _running {true};
    std::chrono::duration<GameTic, std::milli> _msPerUpdate {1000.f/ 60};


    void processInput();
    void update();
    void render();
};


#endif //SPC_PROJECT_GAMELOOP_H
