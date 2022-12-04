//
// Created by Lucas on 4-12-2022.
//

#ifndef GOLFENGINE_ASTARPATHFINDINGSERVICE_H
#define GOLFENGINE_ASTARPATHFINDINGSERVICE_H

#include "Abstracts/PathfindingService.h"

namespace GolfEngine::Services::Pathfinding{

    class AStarPathfindingService : public PathfindingService {
    private:

    public:
        AStarPathfindingService();
        void findPath() override;


    };
}
#endif //GOLFENGINE_ASTARPATHFINDINGSERVICE_H
