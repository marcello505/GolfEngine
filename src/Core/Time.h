//
// Created by marcello on 11/7/22.
//

#ifndef GOLFENGINE_TIME_H
#define GOLFENGINE_TIME_H

#include <chrono>

typedef float GameTic;

namespace GolfEngine::Core{
    class Time {
    public:
        //Methods
        /// Gets the current render fps
        /// \return render fps
        static GameTic getRenderFps();
        /// Gets the current physics fps
        /// \return
        static GameTic getPhysicsFps();
        /// Gets the delta time of the render frames
        /// \return render delta time
        [[nodiscard]] GameTic getRenderDeltaTime() const;
        /// Gets the delta time of the physics frames
        /// \return physics delta time
        static GameTic getPhysicsDeltaTime();
        /// Gets the time scale of the game loop
        /// \return time scale of game loop
        static GameTic getTimeScale();
        /// Sets the time scale fo the game loop (influences the updates made in the physics world and scene)
        /// \param timeScale to be set
        static void setTimeScale(GameTic timeScale);

        void measureRenderCall();
        void measurePhysicsCall();
    private:

        //Fields
        std::chrono::duration<GameTic, std::milli> _interval {500};
        std::chrono::steady_clock::time_point _previousRenderCall = std::chrono::steady_clock::now();
        std::chrono::duration<GameTic, std::milli> _renderFpsCounter {0.f};
        std::chrono::steady_clock::time_point _previousPhysicsCall = std::chrono::steady_clock::now();
        std::chrono::duration<GameTic, std::milli> _physicsFpsCounter {0.f};
        GameTic _renderDeltaTime {};
        static GameTic _physicsDeltaTime;
        int _physicsCalls {0};
        int _renderCalls {0};
        static GameTic _fpsPhysics;
        static GameTic _fpsRender;
        static GameTic _timeScale;
    };
}


#endif //GOLFENGINE_TIME_H
