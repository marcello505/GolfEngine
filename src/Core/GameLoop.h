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
#include "../Services/Abstracts/TileMapParserService.h"
#include "../Services/Abstracts/PathfindingService.h"
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
    void setTileMapParserService(TileMapParserService* tileMapParserService);
    void setPathfindingService(PathfindingService* pathfindingService);
    void setFramesPerSeccond(GameTic fps);
    [[nodiscard]] bool isGameRunning() const;

    //Methods
    void useDefaultServices();
    void start();
    void stop();

private:
    bool _running {true};
    std::chrono::duration<GameTic, std::milli> _msPerUpdate {1000.f/ 60};

    void processInput();
    void update();
    void render();
    static void findPaths();
};


#endif //SPC_PROJECT_GAMELOOP_H
