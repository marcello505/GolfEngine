//
// Created by marcello on 11/8/22.
//

#include <memory>
#define GOLFENGINE_SINGLETON_PRIVATE
#include "PhysicsSingleton.h"

namespace GolfEngine::Services::Physics{
    std::unique_ptr<PhysicsService> globalPhysicsInstance {};

    PhysicsService* getService() {
        if(globalPhysicsInstance){
            return globalPhysicsInstance.get();
        }
        else{
            return nullptr;
        }
    }

    void setService(PhysicsService* service) {
        globalPhysicsInstance.reset(service);
    }

    bool hasService() {
        return (bool)globalPhysicsInstance;
    }
}

