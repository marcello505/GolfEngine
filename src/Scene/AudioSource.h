//
// Created by jaaps on 02/11/2022.
//

#ifndef GOLFENGINE_AUDIOSOURCE_H
#define GOLFENGINE_AUDIOSOURCE_H


#include <string>

class AudioSource {

public:
    std::string audioClip;
    bool playOnAwake;
    bool loop;
    int volume;
    void play(bool loop);
    void stop();
};


#endif //GOLFENGINE_AUDIOSOURCE_H
