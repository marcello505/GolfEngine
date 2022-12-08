//
// Created by Lucas on 7-12-2022.
//

#ifndef GOLFENGINE_GRAPH_H
#define GOLFENGINE_GRAPH_H

#include <utility>
#include <vector>
#include "./Node.h"
#include "../../validation/US00_Rendering/RectDrawable.h"
#include <map>

struct Graph {
    explicit Graph(std::vector<Node> nodes) : nodes{std::move(nodes)}{

    }
    std::vector<Node> nodes;
    std::map<int, RectDrawable*> drawables;

};

#endif //GOLFENGINE_GRAPH_H
