//
// Created by marcello on 11/8/22.
//

#include "PhysicsSingleton.h"

std::unique_ptr<PhysicsService> globalPhysicsInstance {};

PhysicsService* GolfEngine::Services::Physics::getService() {
    if(globalPhysicsInstance){
        return globalPhysicsInstance.get();
    }
    else{
        return nullptr;
    }
}

void GolfEngine::Services::Physics::setService(PhysicsService* service) {
    globalPhysicsInstance.reset(service);
}

bool GolfEngine::Services::Physics::hasService() {
    return (bool)globalPhysicsInstance;
}
