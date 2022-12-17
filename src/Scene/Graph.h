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

class Graph : Drawable {
public:
    explicit Graph(std::vector<Node> nodes, std::vector<std::unique_ptr<RectRenderShape>> drawables);
    ~Graph() override;

    //Rule of Five
    Graph(const Graph& other) = delete;
    Graph(const Graph&& other) = delete;
    Graph& operator=(const Graph& other) = delete;
    Graph& operator=(const Graph&& other) = delete;

    std::vector<Node> nodes {};
    RenderShape& getRenderShape() override;
    void updateGraphColors();
private:
    GraphRenderShape _renderShape {};
};

#endif //GOLFENGINE_GRAPH_H
