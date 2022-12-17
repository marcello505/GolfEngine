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
    virtual void createGraph() = 0;
    virtual Graph& getGraph() = 0;
    virtual Node& covertPosToNode(Vector2 position) = 0;
    virtual void setNodeDistance(int nodeDistance) = 0;
    virtual void setMarginAroundRectColliders(int margin) = 0;
    virtual void setGraphSize(int width, int height) = 0;
    virtual void setMaxPathsToCalculatePerTic(int maxPathsPerTic) = 0;

    // Virtual destructor
    virtual ~PathfindingService() = default;
};


#endif //GOLFENGINE_PATHFINDINGSERVICE_H
