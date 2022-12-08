//
// Created by conner on 11/24/2022.
//

#include "DrawPathScript.h"

void DrawPathScript::onStart() {
    pathfinding = _gameObject->get().getComponent<Pathfinding>();
}

void DrawPathScript::onUpdate() {
    if(!pathfinding->get().getPath().empty()){
        auto graph = pathfinding->get().getGraph();

        for (const auto& nodes : graph->nodes ) {
            if(nodes.tag == NodeTags::Visited){
                graph->drawables.at(nodes.id)->setColor(Color(0,0,255));
            }
        }



        for (const auto& node : pathfinding->get().getPath()) {
            graph->drawables.at(node.id)->setColor(Color(0,255,0));
        }

        // Display weigted nodes
        graph->drawables.at(graph->nodes[131].id)->setColor(Color(255,0,0));
        graph->drawables.at(graph->nodes[100].id)->setColor(Color(255,0,0));
        graph->drawables.at(graph->nodes[69].id)->setColor(Color(255,0,0));
        graph->drawables.at(graph->nodes[38].id)->setColor(Color(255,0,0));
        graph->drawables.at(graph->nodes[7].id)->setColor(Color(255,0,0));

    }
}
