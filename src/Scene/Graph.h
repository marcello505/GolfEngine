//
// Created by Lucas on 7-12-2022.
//

#ifndef GOLFENGINE_GRAPH_H
#define GOLFENGINE_GRAPH_H

#include <utility>
#include <vector>
#include "./Node.h"
#include "Scene/Components/Drawable.h"
#include "Scene/RenderShape/GraphRenderShape.h"
#include <map>

namespace GolfEngine::Scene {
    class Graph : Components::Drawable {
    public:
        /// Graph object to manage a graph used in pathfinding
        /// \param nodes list of nodes inside graph
        /// \param drawables list of drawable nodes
        explicit Graph(std::vector<Node> nodes, std::vector<std::unique_ptr<Render::RectRenderShape>> drawables);

        ~Graph() override;

        //Rule of Five
        Graph(const Graph &other) = delete;
        Graph(const Graph &&other) = delete;
        Graph &operator=(const Graph &other) = delete;
        Graph &operator=(const Graph &&other) = delete;

        Render::RenderShape &getRenderShape() override;

        /// Updates the list of drawables based on included in path, visited or unvisited
        void updateGraphColors();

        std::vector<Node> nodes{};
    private:
        Render::GraphRenderShape _renderShape{};
    };
}

#endif //GOLFENGINE_GRAPH_H
