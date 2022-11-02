//
// Created by Lucas on 2-11-2022.
//

#ifndef SPC_PROJECT_GAMELOOP_H
#define SPC_PROJECT_GAMELOOP_H

//TODO Remove this if Skeleton/services is finished
class AudioService;
class InputService;
class RenderService;
class PhysicsService;

class GameLoop {
public:
    void setAudioService(const AudioService& audioService);
    void setInputService(const InputService& inputService);
    void setRenderService(const RenderService& renderService);
    void setPhysicsService(const PhysicsService& physicsService);
    bool isGameRunning() const;
    void start();
    void stop();
};


#endif //SPC_PROJECT_GAMELOOP_H
