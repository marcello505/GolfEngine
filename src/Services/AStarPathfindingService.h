//
// Created by Lucas on 4-12-2022.
//

#ifndef GOLFENGINE_ASTARPATHFINDINGSERVICE_H
#define GOLFENGINE_ASTARPATHFINDINGSERVICE_H

#include "Abstracts/PathfindingService.h"
#include <limits>
#include <queue>
#include <functional>

namespace GolfEngine::Services::Pathfinding{
    using node_priority_queue = std::priority_queue<
           Node, std::vector<Node>, std::function<bool(const Node &, const Node &)>>;



    class AStarPathfindingService : public PathfindingService {
    private:
        std::vector<std::reference_wrapper<class Pathfinding>> _pathfindingComponents ;

    public:
        AStarPathfindingService();
        std::vector<Node> findPath(Node& start, Node& target,Graph& graph) override;
        void addPathfinding(class Pathfinding& pathfinding) override;

        void removePathfinding(class Pathfinding& pathfinding) override;

        int calculateHeuristic(Node n, Node target);

        void findPathEveryTick() override;
    };

    struct heuristicValues {
        //g = costs from start to current cell
        //h = estimated costs from current to final cell
        //f = sum of G + H
        // parent = ID of parent

        int g, h, f, parent;
        heuristicValues() : g(0), h(std::numeric_limits<int>::max()), f(std::numeric_limits<int>::max()), parent(-1) {}
        heuristicValues(int _g, int _h, int _f, int _parent)
                : g(_g), h(_h), f(_f), parent(_parent) {}
    };
}
#endif //GOLFENGINE_ASTARPATHFINDINGSERVICE_H
