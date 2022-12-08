//
// Created by jaaps on 02/11/2022.
//

#include "Pathfinding.h"

#include <utility>
#include "Services/Abstracts/PathfindingService.h"
#include "Services/Singletons/PathfindingSingleton.h"

Pathfinding::Pathfinding(GameObject *target, std::shared_ptr<Graph> graph) : _target{*target}, _graph{std::move(graph)} {

}

void Pathfinding::navigateToPosition() {


}

Node& Pathfinding::covertPosToNode(Vector2 position){
    //TODO get max flaot
    Vector2 smallest = {99999.0, 99999.0};
    int smallestNodeId = _graph->nodes[0].id;
    for (auto& node : _graph->nodes) {
        auto xDiff = getBiggestNumber(position.x, node.position.x) -
                getSmallestNumber(position.x, node.position.x);
        auto yDiff = getBiggestNumber(position.y, node.position.y) -
                     getSmallestNumber(position.y, node.position.y);
        if( xDiff < smallest.x && yDiff < smallest.y ){
            smallest.x = xDiff;
            smallest.y = yDiff;
            smallestNodeId = node.id;
        }
    }
    return _graph->nodes[smallestNodeId];
}

int Pathfinding::getSmallestNumber(int first, int second){
        if(first < second){
            return first;
        }
        return second;

}

int Pathfinding::getBiggestNumber(int first, int second){
    if(first > second){
        return first;
    }
    return second;

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

std::shared_ptr<Graph> Pathfinding::getGraph() {
    return _graph;
}




