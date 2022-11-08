//
// Created by marcello on 11/8/22.
//

#include "InputSingleton.h"
#include <memory>

namespace GolfEngine::Services::Input{
    std::unique_ptr<InputService> globalInputInstance {};

    InputService* getService() {
        if(globalInputInstance){
            return globalInputInstance.get();
        }
        else{
            return nullptr;
        }
    }

    void setService(InputService* service) {
        globalInputInstance.reset(service);
    }

    bool hasService() {
        return (bool)globalInputInstance;
    }
}