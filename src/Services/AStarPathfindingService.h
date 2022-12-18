//
// Created by Lucas on 4-12-2022.
//

#ifndef GOLFENGINE_ASTARPATHFINDINGSERVICE_H
#define GOLFENGINE_ASTARPATHFINDINGSERVICE_H

#include "Abstracts/PathfindingService.h"
#include "Scene/Components/Collider.h"
#include <limits>
#include <queue>
#include <functional>

namespace GolfEngine::Services::Pathfinding{
    ///small queue used to determine where nodes needs to be placed
    using node_priority_queue = std::priority_queue<
       Node, std::vector<Node>, std::function<bool(const Node &, const Node &)>>;

    class AStarPathfindingService : public PathfindingService {
    private:
        std::vector<std::reference_wrapper<class Pathfinding>> _pathfindingComponents ;
        std::unique_ptr<Graph> _graph;
        int _nodeDistance {50};
        int rectMargin{0};

        int _graphWidth {1920};
        int _graphHeight {1080};
        int _graphStartPointX {0};
        int _graphStartPointY {0};
        int _maxPathsToCalculatePerTic {1};

    public:
        AStarPathfindingService() = default;

        // Pathfinding Service overrides
        std::vector<Node> findPath(Node& start, Node& target, Graph& graph) override;
        void addPathfinding(class Pathfinding& pathfinding) override;
        void removePathfinding(class Pathfinding& pathfinding) override;
        void findPathEveryTick() override;
        void createGraph() override;
        Graph& getGraph() override;
        Node &covertPosToNode(Vector2 position) override;
        void setNodeDistance(int nodeDistance) override;
        void setMarginAroundRectColliders(int margin) override;
        void setGraphSize(int width, int height) override;
        void setGraphStartPoint(int x, int y) override;
        void setMaxPathsToCalculatePerTic(int maxPathsPerTic) override;

        /// Calculation that estimates distance between two nodes
        /// \param n Neighbour node that is used as start node in calculation
        /// \param target Node that us used as end point in calculation
        /// \return Estimated distance between n and target
        int calculateHeuristic(const Node& n, const Node& target);

        /// Checks if position is a spot where game object can move to
        /// \param pos position that is used point to check
        /// \return Returns true if position is in valid open spot
        [[nodiscard]] bool isValidSpot(Vector2 pos) const;
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
