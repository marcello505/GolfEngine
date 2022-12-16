//
// Created by Lucas on 7-12-2022.
//

#ifndef GOLFENGINE_GRAPH_H
#define GOLFENGINE_GRAPH_H

#include <utility>
#include <vector>
#include "./Node.h"
#include "PathDrawable.h"
#include <map>

struct Graph {
    explicit Graph(std::vector<Node> nodes) : nodes{std::move(nodes)}{

    }
    std::vector<Node> nodes;
    std::map<int, PathDrawable*> drawables;

};

#endif //GOLFENGINE_GRAPH_H
