//
// Created by marcello on 11/7/22.
//

#ifndef GOLFENGINE_TIME_H
#define GOLFENGINE_TIME_H

#include <chrono>

typedef float GameTic;

namespace GolfEngine{
    class Time {
    public:

        //Methods
        static GameTic getRenderFps();
        static GameTic getPhysicsFps();
        GameTic getRenderDeltaTime() const;
        static GameTic getPhysicsDeltaTime();
        static GameTic getTimeScale();
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
