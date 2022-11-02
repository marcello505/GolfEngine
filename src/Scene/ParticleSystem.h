//
// Created by jaaps on 02/11/2022.
//

#ifndef GOLFENGINE_PARTICLESYSTEM_H
#define GOLFENGINE_PARTICLESYSTEM_H

#include "Component.h"
class ParticleSystem : public Component{
public:

    void play(bool looping);
    void stop();
private:
    int _particlesPerSecond;
    float _duration;
};


#endif //GOLFENGINE_PARTICLESYSTEM_H
