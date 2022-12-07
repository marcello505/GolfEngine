//
// Created by Lucas on 7-12-2022.
//

#ifndef GOLFENGINE_CREATEGRAPH_H
#define GOLFENGINE_CREATEGRAPH_H


#include "Scene/Vector2.h"
#include "Scene/Components/Collider.h"
#include "Scene/Graph.h"

class CreateGraph {
    [[nodiscard]] bool isValidSpot(Vector2 pos, std::vector<Collider*> colliders) const;

public:
    CreateGraph(std::vector<Collider *> colliders, int nodeDistance);


    Graph& createGraph();

    int _nodeDistance;
    std::vector<Collider *> colliders;

};


#endif //GOLFENGINE_CREATEGRAPH_H
