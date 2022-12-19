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

    /// Resets the _previous field to the current time. This essentially makes it so that no time has passed between the last tic and the current tic.
    /// This has the effect that the gameloop will stop trying to catch up with the physics frames that were "too late".
    /// Mainly used by SceneManager to ignore the lost time when switching scenes
    void resetLag();

private:
    bool _running {true};
    std::chrono::duration<GameTic, std::milli> _msPerUpdate {1000.f/ 60};

    /// This holds the specific timepoint when the last game tic was handled.
    std::chrono::steady_clock::time_point _previous {};

    void processInput();
    void update();
    void render();
    static void findPaths();
};

namespace GolfEngine::Core{
    GameLoop& getRunningGameLoop();
}

#endif //SPC_PROJECT_GAMELOOP_H
