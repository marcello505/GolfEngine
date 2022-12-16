//
// Created by Lucas on 2-12-2022.
//

#ifndef GOLFENGINE_PATHFINDINGSINGLETON_H
#define GOLFENGINE_PATHFINDINGSINGLETON_H

#include "../Abstracts/PathfindingService.h"

namespace GolfEngine::Services::Pathfinding{
    PathfindingService* getService();
    bool hasService();
#ifdef GOLFENGINE_SINGLETON_PRIVATE
    void setService(PathfindingService* service);
#endif
}



#endif //GOLFENGINE_PATHFINDINGSINGLETON_H
