//
// Created by Lucas on 2-12-2022.
//

#ifndef GOLFENGINE_PATHFINDINGSINGLETON_H
#define GOLFENGINE_PATHFINDINGSINGLETON_H

#include "../Abstracts/PathfindingService.h"

namespace GolfEngine::Services::Pathfinding{
    /// Retrieves the global instance of the Pathfinding Service
    /// \return pointer reference to service
    PathfindingService* getService();

    /// Checks whether there is an active global service
    /// \return true if there is an active global service
    bool hasService();
#ifdef GOLFENGINE_SINGLETON_PRIVATE
    void setService(PathfindingService* service);
#endif
}



#endif //GOLFENGINE_PATHFINDINGSINGLETON_H
