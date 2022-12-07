//
// Created by Lucas on 7-12-2022.
//

#ifndef GOLFENGINE_GRAPH_H
#define GOLFENGINE_GRAPH_H

#include <vector>
#include "./Node.h"

struct Graph {
    Graph(std::vector<Node> nodes) : nodes{nodes}{

    }
    std::vector<Node> nodes;


};

#endif //GOLFENGINE_GRAPH_H
