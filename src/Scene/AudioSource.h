//
// Created by jaaps on 02/11/2022.
//

#ifndef GOLFENGINE_AUDIOSOURCE_H
#define GOLFENGINE_AUDIOSOURCE_H


#include <string>
#include "Collider.h"

class AudioSource : public Collider{

public:
    void play(bool loop);
    void stop();
private:
    std::string _audioClip;
    bool _playOnAwake;
    bool _loop;
    int _volume;
};


#endif //GOLFENGINE_AUDIOSOURCE_H
