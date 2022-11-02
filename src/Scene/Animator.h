//
// Created by jaaps on 02/11/2022.
//

#ifndef GOLFENGINE_ANIMATOR_H
#define GOLFENGINE_ANIMATOR_H


#include <string>
#include <map>
#include "Animation.h"

class Animator {
public:
    int fps;
    void play(std::string animation, bool looping);
    void stop();
private:
    std::map<std::string, Animation> _animations;
};


#endif //GOLFENGINE_ANIMATOR_H
