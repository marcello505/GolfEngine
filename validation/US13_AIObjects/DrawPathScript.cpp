//
// Created by conner on 11/24/2022.
//

#include "DrawPathScript.h"
#include "Services/Singletons/PathfindingSingleton.h"
#include "Scene/Components/RigidBody.h"

void DrawPathScript::onStart() {
    pathfinding = _gameObject->get().getComponent<Pathfinding>();
}

void DrawPathScript::onUpdate() {
auto direction = pathfinding->get().getNewDirection();


    auto rb = &_gameObject.value().get().getComponent<RigidBody>();
    rb->applyForceToCenter(direction * 0.05);

    if(!pathfinding->get().getPath().empty()){
        auto graph = GolfEngine::Services::Pathfinding::getService()->getGraph();

        for (const auto& nodes : graph.nodes ) {
            if(nodes.tag == NodeTags::Visited){
                graph.drawables.at(nodes.id)->setColor(Color(0,0,255));
            }
        }



        for (const auto& node : pathfinding->get().getPath()) {
            graph.drawables.at(node.id)->setColor(Color(0,255,0));
        }
    }
}
