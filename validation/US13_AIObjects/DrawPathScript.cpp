//
// Created by conner on 11/24/2022.
//

#include "DrawPathScript.h"
#include "Services/Singletons/PathfindingSingleton.h"

void DrawPathScript::onStart() {
    pathfinding = _gameObject->get().getComponent<Pathfinding>();
}

void DrawPathScript::onUpdate() {

    if(!pathfinding->get().getPath().empty()){
        auto graph = GolfEngine::Services::Pathfinding::getService()->getGraph();

        for (const auto& nodes : graph->nodes ) {
            if(nodes.tag == NodeTags::Visited){
                graph->drawables.at(nodes.id)->setColor(Color(0,0,255));
            }
        }



        for (const auto& node : pathfinding->get().getPath()) {
            graph->drawables.at(node.id)->setColor(Color(0,255,0));
        }
    }
}
