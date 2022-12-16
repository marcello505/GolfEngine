//
// Created by Lucas on 2-12-2022.
//

#include <memory>
#define GOLFENGINE_SINGLETON_PRIVATE
#include "PathfindingSingleton.h"

namespace GolfEngine::Services::Pathfinding{
    std::unique_ptr<PathfindingService> globalPathfindingInstance {};

    PathfindingService* getService() {
        if(globalPathfindingInstance){
            return globalPathfindingInstance.get();
        }
        else{
            return nullptr;
        }
    }

    void setService(PathfindingService* service) {
        globalPathfindingInstance.reset(service);
    }

    bool hasService() {
        return (bool)globalPathfindingInstance;
    }
}

