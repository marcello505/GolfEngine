//
// Created by conner on 11/8/2022.
//

//TODO Add preprocessor commands to hide setService
//#define GOLFENGINE_SINGLETON_PRIVATE
#include "RenderSingleton.h"
#include <memory>

namespace GolfEngine::Services::Render{
    std::unique_ptr<RenderService> globalRenderService {};

    RenderService* getService() {
        if(globalRenderService){
            return globalRenderService.get();
        }
        else{
            return nullptr;
        }
    }

    void setService(RenderService* service){
        globalRenderService.reset(service);
    }

    bool hasService(){
        return (bool)globalRenderService;
    }
}

