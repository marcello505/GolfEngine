//
// Created by jaaps on 02/11/2022.
//

#ifndef GOLFENGINE_PARTICLESYSTEM_H
#define GOLFENGINE_PARTICLESYSTEM_H


class ParticleSystem {
public:
    int particlesPerSecond;
    float duration;
    void play(bool looping);
    void stop();

};


#endif //GOLFENGINE_PARTICLESYSTEM_H
