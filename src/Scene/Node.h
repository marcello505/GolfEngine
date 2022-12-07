//
// Created by Lucas on 7-12-2022.
//

#ifndef GOLFENGINE_NODE_H
#define GOLFENGINE_NODE_H

#include <string>
#include <vector>
#include "./Vector2.h"

struct Node{
    Node(int id, Vector2 position) : id{id}, position{position},visited{false}, tag{"none"}{}

    int id;
    Vector2 position;
    bool visited;
    std::string tag;

    std::vector<int> edges {};
};
#endif //GOLFENGINE_NODE_H
