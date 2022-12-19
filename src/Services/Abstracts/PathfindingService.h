//
// Created by Lucas on 2-12-2022.
//

#ifndef GOLFENGINE_PATHFINDINGSERVICE_H
#define GOLFENGINE_PATHFINDINGSERVICE_H

#include <map>
#include <vector>
#include "Scene/Graph.h"
#include "Scene/Components/Pathfinding.h"

using namespace GolfEngine::Scene;
using namespace GolfEngine::Scene::Components;

namespace GolfEngine::Services::Pathfinding {
    class PathfindingService {
    public:
        /// Return path to given nodes
        /// \param start Node where path needs to start
        /// \param target node that needs to be found
        /// \param graph Graph where all nodes can be found
        /// \return
        virtual std::vector<Node> findPath(Node &start, Node &target, Graph &graph) = 0;

        /// registers component auto update its own path
        /// \param pathfinding component that needs updates
        virtual void addPathfinding(Components::Pathfinding &pathfinding) = 0;

        /// removes component from registered components
        /// \param pathfinding component that needs to be removed
        virtual void removePathfinding(Components::Pathfinding &pathfinding) = 0;

        /// Is called every game tixk and checks if any registered components needs to be updated
        virtual void findPathEveryTick() = 0;

        /// Generates a graph in the scene
        virtual void createGraph() = 0;

        /// Gets the current generated graph
        /// \return Reference to the graph object
        virtual Graph &getGraph() = 0;

        /// Returns node closest to position
        /// \param position position where node should be
        /// \return Returns node closest to given position
        virtual Node &covertPosToNode(Vector2 position) = 0;

        /// Determines the distance between all nodes in graph
        /// \param nodeDistance distance between each node
        virtual void setNodeDistance(int nodeDistance) = 0;

        /// Creates a margin around al rect colliders to avoid objects getting stuck
        /// \param margin the margin around the rectangles.
        virtual void setMarginAroundRectColliders(int margin) = 0;

        /// Set the width and height of the graph that is created.
        /// \param width width in world space (pixels)
        /// \param height height in world space (pixels)
        virtual void setGraphSize(int width, int height) = 0;

        /// Sets the start point of where the graph should be generated in the scene
        /// \param x position
        /// \param y position
        virtual void setGraphStartPoint(int x, int y) = 0;

        /// Set the maximum amount of paths to process each tic.
        /// By default this is set to 1
        /// \param maxPathsPerTic an integer of 1 or more
        virtual void setMaxPathsToCalculatePerTic(int maxPathsPerTic) = 0;

        // Virtual destructor
        virtual ~PathfindingService() = default;
    };
}


#endif //GOLFENGINE_PATHFINDINGSERVICE_H
