//
// Created by jaaps on 02/11/2022.
//

#include "Pathfinding.h"

#include <utility>
#include <valarray>
#include "Services/Abstracts/PathfindingService.h"
#include "Services/Singletons/PathfindingSingleton.h"

Pathfinding::Pathfinding(GameObject *target, float recalculatePathTime) : _target{*target}, _fps{60},_recalculatePathTime{recalculatePathTime}  {
}



void Pathfinding::onStart() {
    GolfEngine::Services::Pathfinding::getService()->addPathfinding(*this);
    _countedFrames = 120;

}

void Pathfinding::onUpdate() {
    _countedFrames ++;
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

bool Pathfinding::needsNewPath() {
    if(_countedFrames >= _fps * _recalculatePathTime ){
        _countedFrames = 0;
        return true;
    }
    return false;
}





