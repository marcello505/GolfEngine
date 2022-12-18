//
// Created by marcello on 11/8/22.
//

#ifndef GOLFENGINE_INPUTSINGLETON_H
#define GOLFENGINE_INPUTSINGLETON_H

#include "../Abstracts/InputService.h"

namespace GolfEngine::Services::Input{
    /// Retrieves the global instance of the Input Service
    /// \return pointer reference to service
    InputService* getService();

    /// Checks whether there is an active global service
    /// \return true if there is an active global service
    bool hasService();
#ifdef GOLFENGINE_SINGLETON_PRIVATE
    void setService(InputService* service);
#endif
}

#endif //GOLFENGINE_INPUTSINGLETON_H
