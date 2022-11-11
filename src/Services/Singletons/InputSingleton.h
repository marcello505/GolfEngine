//
// Created by marcello on 11/8/22.
//

#ifndef GOLFENGINE_INPUTSINGLETON_H
#define GOLFENGINE_INPUTSINGLETON_H

#include "../Abstracts/InputService.h"

namespace GolfEngine::Services::Input{
    InputService* getService();
    bool hasService();
#ifdef GOLFENGINE_SINGLETON_PRIVATE
    void setService(InputService* service);
#endif
}

#endif //GOLFENGINE_INPUTSINGLETON_H
