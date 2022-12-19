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

using namespace GolfEngine::Services;

namespace GolfEngine::Core {
    class GameLoop {
    public:
        //Fields
        std::unique_ptr<Time> time = std::make_unique<Time>();

        //Getters and Setters
        /// Set custom AudioService
        /// \param audioService to bet set
        void setAudioService(Services::Audio::AudioService *audioService);

        /// Set custom InputService
        /// \param inputService to bet set
        void setInputService(Services::Input::InputService *inputService);

        /// Set custom RenderService
        /// \param renderService to bet set
        void setRenderService(Services::Render::RenderService *renderService);

        /// Set custom PhysicsService
        /// \param physicsService to bet set
        void setPhysicsService(Services::Physics::PhysicsService *physicsService);

        /// Set custom TileMapParserService
        /// \param tileMapParserService to bet set
        void setTileMapParserService(Services::TileMapParser::TileMapParserService *tileMapParserService);

        /// Set custom PathfindingService
        /// \param pathfindingService to bet set
        void setPathfindingService(Services::Pathfinding::PathfindingService *pathfindingService);

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

    GameLoop &getRunningGameLoop();
}
#endif //SPC_PROJECT_GAMELOOP_H
