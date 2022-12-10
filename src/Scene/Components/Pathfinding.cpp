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
    std::reverse(_path.begin(), _path.end());
    _gameObject->get().setWorldTransform(Transform(Vector2(_path[0].position.x,
                                                           _path[0].position.y), 0, Vector2(1,1)));
    getNewDirection();
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

Vector2 Pathfinding::getNewDirection()
{
    Vector2 newDir;
    Vector2 nextPos;

    // get node that matches with current position of parent
    Node& currentNode = GolfEngine::Services::Pathfinding::getService()->
            covertPosToNode(getParentGameObjectPosition());

    int nodeCounter = 1;
    for(auto& node : _path){ //check for all nodes in the path
        if(currentNode.id == node.id){ //if it matches with the current node the parent is in
            nextPos = _path[nodeCounter + 1].position; //get position of next node
            break;
        }
        else if(nodeCounter == _path.size()){ // if the current node is not in the path
            nextPos = _path[0].position;
        }
        nodeCounter ++;
    }

    //set new direction
    if(nextPos.x < currentNode.position.x && nextPos.y == currentNode.position.y){ // left
        newDir = Vector2(-1, 0);
    }else if(nextPos.x > currentNode.position.x && nextPos.y == currentNode.position.y){ // right
        newDir = Vector2(1, 0);
    }else if(nextPos.y < currentNode.position.y && nextPos.x == currentNode.position.x){ // up
        newDir = Vector2(0, -1);
    }else if(nextPos.y > currentNode.position.y && nextPos.x == currentNode.position.x){ // down
        newDir = Vector2(0, 1);
    }else if(nextPos.x < currentNode.position.x && nextPos.y < currentNode.position.y){ // leftUp
        newDir = Vector2(-1, -1);
    }else if(nextPos.x < currentNode.position.x && nextPos.y > currentNode.position.y){ // leftDown
        newDir = Vector2(-1, 1);
    }else if(nextPos.x > currentNode.position.x && nextPos.y < currentNode.position.y){ // rightUp
        newDir = Vector2(1, -1);
    }else if(nextPos.x > currentNode.position.x && nextPos.y > currentNode.position.y){ // rightDown
        newDir = Vector2(1, 1);
    }

    return newDir;
}





