//
// Created by conner on 11/8/2022.
//

#ifndef GOLFENGINE_RENDERSINGLETON_H
#define GOLFENGINE_RENDERSINGLETON_H

#include "../Abstracts/RenderService.h"

namespace GolfEngine::Services::Render{
    /// Retrieves the global instance of the Render Service
    /// \return pointer reference to service
    RenderService* getService();

    /// Checks whether there is an active global service
    /// \return true if there is an active global service
    bool hasService();
    //TODO Add preprocessor commands to hide setService
//#ifdef GOLFENGINE_SINGLETON_PRIVATE
    void setService(RenderService* service);
//#endif
}


#endif //GOLFENGINE_RENDERSINGLETON_H
