//
// Created by Lucas on 2-11-2022.
//

#ifndef SPC_PROJECT_GAMELOOP_H
#define SPC_PROJECT_GAMELOOP_H

#include <memory>
#include "../Services/Abstracts/AudioService.h"
#include "../Services/Abstracts/InputService.h"
#include "../Services/Abstracts/RenderService.h"
#include "../Services/Abstracts/PhysicsService.h"
#include "SceneManager.h"

class GameLoop {
public:
    GameLoop();
    void setAudioService(const AudioService& audioService);
    void setInputService(const InputService& inputService);
    void setRenderService(const RenderService& renderService);
    void setPhysicsService(const PhysicsService& physicsService);
    bool isGameRunning() const;
    void start();
    void stop();
};


#endif //SPC_PROJECT_GAMELOOP_H
