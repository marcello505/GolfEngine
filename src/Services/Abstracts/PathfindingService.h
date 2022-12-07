//
// Created by Lucas on 2-12-2022.
//

#ifndef GOLFENGINE_PATHFINDINGSERVICE_H
#define GOLFENGINE_PATHFINDINGSERVICE_H

#include <map>
#include <vector>
#include "Scene/Graph.h"
#include "Scene/Components/Pathfinding.h"

class PathfindingService {
public:
    virtual std::vector<Node> findPath(Node& start, Node& target, Graph& graph) = 0;

    virtual void addPathfinding(Pathfinding& pathfinding) = 0;

    virtual void removePathfinding(Pathfinding& pathfinding)= 0;

    virtual void findPathEveryTick() = 0;


};


#endif //GOLFENGINE_PATHFINDINGSERVICE_H
