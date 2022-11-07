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
        GameTic getRenderFps() const;
        GameTic getPhysicsFps() const;
        GameTic getRenderDeltaTime() const;
        GameTic getPhysicsDeltaTime() const;

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
        GameTic _physicsDeltaTime {};
        int _physicsCalls {0};
        int _renderCalls {0};
        GameTic _fpsPhysics {0};
        GameTic _fpsRender {0};
    };

}


#endif //GOLFENGINE_TIME_H
