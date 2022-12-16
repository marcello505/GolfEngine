//
// Created by Lucas on 7-12-2022.
//

#ifndef GOLFENGINE_NODE_H
#define GOLFENGINE_NODE_H

#include <string>
#include <vector>
#include "./Vector2.h"

enum class NodeTags {
    None,
    Visited,
    Path

};
struct Node{
    Node(int id, Vector2 position, int weight = 1) : id{id}, position{position}, weight{weight}, tag{NodeTags::None}{}

    int id;
    Vector2 position;
    NodeTags tag;
    int weight;

    std::vector<int> edges {};
};




#endif //GOLFENGINE_NODE_H
