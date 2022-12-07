//
// Created by Lucas on 2-12-2022.
//

#ifndef GOLFENGINE_PATHFINDINGSERVICE_H
#define GOLFENGINE_PATHFINDINGSERVICE_H

#include <map>
#include <vector>
#include "Scene/Graph.h"

class PathfindingService {
public:
    virtual std::vector<Node> findPath(const Node& start, const Node& target,const Graph& graph) = 0;
};
#endif //GOLFENGINE_PATHFINDINGSERVICE_H
