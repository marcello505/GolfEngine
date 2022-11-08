//
// Created by conner on 11/8/2022.
//

#ifndef GOLFENGINE_RENDERSINGLETON_H
#define GOLFENGINE_RENDERSINGLETON_H

#include "../Abstracts/RenderService.h"

namespace GolfEngine::Services::Render{
    RenderService* getService();
    bool hasService();
    void setService(RenderService* service);
}


#endif //GOLFENGINE_RENDERSINGLETON_H
