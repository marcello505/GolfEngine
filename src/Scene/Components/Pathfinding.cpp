//
// Created by jaaps on 02/11/2022.
//

#include "Pathfinding.h"
#include "Services/Abstracts/PathfindingService.h"
#include "Services/Singletons/PathfindingSingleton.h"
Pathfinding::Pathfinding(GameObject *target, Graph &graph) : _target{*target}, _graph{graph} {

}

void Pathfinding::navigateToPosition() {
    PathfindingService *ps = GolfEngine::Services::Pathfinding::getService();

}

Node& Pathfinding::covertPosToNode(Vector2 position){
    //TODO get max flaot
    Vector2 smalllest = {99999.0, 99999.0};
    Node& smalllestNode = _graph.nodes[0];

    for (auto& node : _graph.nodes) {
        auto xDiff = std::abs(smalllest.x-node.position.x);
        auto yDiff = std::abs(smalllest.y-node.position.y);
        if( xDiff < smalllest.x && yDiff < smalllest.y ){
            smalllest.x = xDiff;
            smalllest.y = yDiff;
            smalllestNode = node;
        }
    }
    return smalllestNode;
}



void Pathfinding::onStart() {
    GolfEngine::Services::Pathfinding::getService()->addPathfinding(*this);

}

void Pathfinding::onUpdate() {
    countedFrames ++;
    if(countedFrames > 120){
        countedFrames =0;
    }
}

void Pathfinding::onRemove() {
    GolfEngine::Services::Pathfinding::getService()->removePathfinding(*this);

}

bool Pathfinding::getActive() {
    return _active;
}

void Pathfinding::setActive(bool active) {
    _active = active;

}

void Pathfinding::setParentGameObject(GameObject &gameObject) {
    _gameObject = gameObject;
}
Vector2 Pathfinding::getParentGameObjectPosition() const  {
    return _gameObject->get().getWorldTransform().position;
}

//void Pathfinding::setTarget(GameObject target) {
//    _target = target;
//}

Vector2 Pathfinding::getTargetPosition() {
    return _target.getWorldTransform().position;
}

Graph &Pathfinding::getGraph() {
    return _graph;
}




