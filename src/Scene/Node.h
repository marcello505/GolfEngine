//
// Created by Lucas on 7-12-2022.
//

#ifndef GOLFENGINE_NODE_H
#define GOLFENGINE_NODE_H

#include <string>
#include <vector>
#include "./Vector2.h"

namespace GolfEngine::Scene {
    enum class NodeTags {
        None,
        Visited,
        Path

    };

    struct Node {
        /// Node used inside graph for pathfinding
        /// \param id unique id of node
        /// \param position position of node
        /// \param weight weight of node
        Node(int id, Vector2 position, int weight = 1) : id{id}, position{position}, weight{weight},
                                                         tag{NodeTags::None} {}

        int id;
        Vector2 position;
        NodeTags tag;
        int weight;

        std::vector<int> edges{};
    };
}


#endif //GOLFENGINE_NODE_H
