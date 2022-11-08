//
// Created by marcello on 11/8/22.
//

#ifndef GOLFENGINE_INPUTSINGLETON_H
#define GOLFENGINE_INPUTSINGLETON_H

#include "../Abstracts/InputService.h"

namespace GolfEngine::Services::Input{
    InputService* getService();
    bool hasService();
    void setService(InputService* service);
}

#endif //GOLFENGINE_INPUTSINGLETON_H
