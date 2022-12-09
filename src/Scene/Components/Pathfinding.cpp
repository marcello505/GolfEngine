//
// Created by jaaps on 02/11/2022.
//

#include "Pathfinding.h"

#include <utility>
#include <valarray>
#include "Services/Abstracts/PathfindingService.h"
#include "Services/Singletons/PathfindingSingleton.h"

Pathfinding::Pathfinding(GameObject *target, std::shared_ptr<Graph> graph) : _target{*target}, _graph{std::move(graph)} {
}



void Pathfinding::onStart() {
    GolfEngine::Services::Pathfinding::getService()->addPathfinding(*this);
    countedFrames = 120;

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

Vector2 Pathfinding::getTargetPosition() {
    return _target.getWorldTransform().position;
}

Node& Pathfinding::covertPosToNode(Vector2 position){
    const auto dist = [position](const auto& p){
        // Change the following to your needs
        return std::pow((p.position.x - position.x), 2) + std::pow((p.position.y - position.y), 2);
    };

    const auto& closest = std::min_element(_graph->nodes.cbegin(), _graph->nodes.cend(),
                                           [&dist](const auto& p1, const auto& p2)
                                           { return dist(p1) < dist(p2); });

    auto& node = *(closest);

    return const_cast<Node &>(node);
}


std::shared_ptr<Graph> Pathfinding::getGraph() {
    return _graph;
}

void Pathfinding::setPath(const std::vector<Node>& path) {
    _path = path;
}

std::vector<Node> Pathfinding::getPath() {
    return _path;
}
//TODO ask if setTarget is needed because it is not possible yet
void Pathfinding::setTarget(GameObject &target) {
   // _target = *target;
}




