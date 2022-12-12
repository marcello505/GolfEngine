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
        int _nodeDistance {20};
        int rectMargin{0};



    public:
        AStarPathfindingService();
        /// Return path to given nodes
        /// \param start Node where path needs to start
        /// \param target node that needs to be found
        /// \param graph Graph where all nodes can be found
        /// \return
        std::vector<Node> findPath(Node& start, Node& target,Graph& graph) override;

        /// registers component auto update its own path
        /// \param pathfinding component that needs updates
        void addPathfinding(class Pathfinding& pathfinding) override;

        /// removes component from registered components
        /// \param pathfinding component that needs to be removed
        void removePathfinding(class Pathfinding& pathfinding) override;

        /// Calculation that estimates distance between two nodes
        /// \param n Neighbour node that is used as start node in calculation
        /// \param target Node that us used as end point in calculation
        /// \return Estimated distance between n and target
        int calculateHeuristic(const Node& n, const Node& target);

        /// Is called every game tixk and checks if any registered components needs to be updated
        void findPathEveryTick() override;

        /// Generates graph
        void createGraph() override;

        /// Gets the current generated graph
        /// \return
        Graph& getGraph() override;

        /// Checks if position is a spot where game object can move to
        /// \param pos position that is used point to check
        /// \return Returns true if position is in valid open spot
        bool isValidSpot(Vector2 pos) const;

        /// Returns node closest to position
        /// \param position position where node should be
        /// \return Returns node closest to given position
        Node &covertPosToNode(Vector2 position);




        /// Determines the distance between all nodes in graph
        /// \param nodeDistance distance between each node
        void setNodeDistance(int nodeDistance) override;

        /// Creates a margin around al rect colliders to avoid objects getting stuck
        /// \param margin the margin around the rectangles.
        void setMarginAroundRectColliders(int margin) override;

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
