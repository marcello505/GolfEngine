//
// Created by jaaps on 02/11/2022.
//

#ifndef GOLFENGINE_ANIMATOR_H
#define GOLFENGINE_ANIMATOR_H


#include <string>
#include <map>
#include "Animation.h"
#include "Collider.h"

class Animator : public Collider {
public:
    void play(const std::string& animation, bool looping);
    void stop();
private:
    std::map<std::string, Animation> _animations;
    int _fps;
};


#endif //GOLFENGINE_ANIMATOR_H
