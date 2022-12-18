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
    /// Set custom AudioService
    /// \param audioService to bet set
    void setAudioService(AudioService *audioService);
    /// Set custom InputService
    /// \param inputService to bet set
    void setInputService(InputService* inputService);
    /// Set custom RenderService
    /// \param renderService to bet set
    void setRenderService(RenderService* renderService);
    /// Set custom PhysicsService
    /// \param physicsService to bet set
    void setPhysicsService(PhysicsService* physicsService);
    /// Set custom TileMapParserService
    /// \param tileMapParserService to bet set
    void setTileMapParserService(TileMapParserService* tileMapParserService);
    /// Set custom PathfindingService
    /// \param pathfindingService to bet set
    void setPathfindingService(PathfindingService* pathfindingService);
    /// Set the fps of the game loop
    /// \param fps to be set
    void setFramesPerSeccond(GameTic fps);
    /// Check whether this GameLoop is running
    /// \return true if currently running
    [[nodiscard]] bool isGameRunning() const;

    //Methods
    /// Initialize the GameLoop object with all default services
    void useDefaultServices();

    /// Start the game loop
    void start();

    /// Stop the game loop
    void stop();

private:
    bool _running {true};
    std::chrono::duration<GameTic, std::milli> _msPerUpdate {1000.f/ 60};

    void processInput();
    void update();
    void render();
    static void findPaths();
};

namespace GolfEngine::Core{
    GameLoop& getRunningGameLoop();
}

#endif //SPC_PROJECT_GAMELOOP_H
