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
        std::chrono::duration<GameTic, std::milli> _interval {1000};
        std::chrono::steady_clock::time_point _previousRenderCall = std::chrono::steady_clock::now();
        std::chrono::duration<GameTic, std::milli> _renderFpsCounter {};
        std::chrono::steady_clock::time_point _previousPhysicsCall = std::chrono::steady_clock::now();
        std::chrono::duration<GameTic, std::milli> _physicsFpsCounter {};
        GameTic _renderDeltaTime {};
        GameTic _physicsDeltaTime {};
        int _physicsCalls {0};
        int _renderCalls {0};
        int _fpsPhysics {0};
        int _fpsRender {0};
    };

}


#endif //GOLFENGINE_TIME_H
