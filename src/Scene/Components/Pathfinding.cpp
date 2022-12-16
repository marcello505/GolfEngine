//
// Created by jaaps on 02/11/2022.
//

#include "Pathfinding.h"

#include <utility>
#include <valarray>
#include "Services/Abstracts/PathfindingService.h"
#include "Services/Singletons/PathfindingSingleton.h"
#include "Services/Singletons/RenderSingleton.h"

Pathfinding::Pathfinding(GameObject *target, float recalculatePathTime) : _target{*target}, _fps{60}, _recalculatePathTime{recalculatePathTime}  {
}



void Pathfinding::onStart() {
    GolfEngine::Services::Pathfinding::getService()->addPathfinding(*this);
    _countedFrames = 120;

}

void Pathfinding::onUpdate() {
    _countedFrames ++;
}

void Pathfinding::onRemove() {
    if( GolfEngine::Services::Pathfinding::getService()){
        GolfEngine::Services::Pathfinding::getService()->removePathfinding(*this);
    }

    if(_pathIsRegistered){
        if(GolfEngine::Services::Pathfinding::hasService()){
            auto& graph = GolfEngine::Services::Pathfinding::getService()->getGraph();

            if(GolfEngine::Services::Render::hasService()){
                auto* rs = GolfEngine::Services::Render::getService();
                for (const auto& drawable : graph.drawables ) {
                    rs->removeDrawable(*drawable.second);
                }
                _pathIsRegistered = false;
            }
        }
    }

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
    return _target.get().getWorldTransform().position;
}

void Pathfinding::setPath(const std::vector<Node>& path) {
    _path = path;
    std::reverse(_path.begin(), _path.end());
}

std::vector<Node> Pathfinding::getPath() {
    return _path;
}

void Pathfinding::setTarget(GameObject &target) {
   _target = target;
}

bool Pathfinding::needsNewPath() {
    if(_countedFrames >= _fps * _recalculatePathTime ){
        _countedFrames = 0;
        return true;
    }
    return false;
}

Vector2 Pathfinding::getPathDirection()
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

    return getDirection(nextPos);
}

void Pathfinding::displayGraph(bool displayPath, bool displayVisited) {
    if(GolfEngine::Services::Pathfinding::hasService()){
        auto& graph = GolfEngine::Services::Pathfinding::getService()->getGraph();

    if(!_pathIsRegistered){
        if(GolfEngine::Services::Render::hasService()){
            auto* rs = GolfEngine::Services::Render::getService();
            for (const auto& drawable : graph.drawables ) {
                rs->addDrawable(*drawable.second);
            }
            _pathIsRegistered = true;
        }
    }


    for (const auto& node : graph.nodes ) {

        graph.drawables.at(node.id)->setColor(Color(255,255,255));
        if(displayVisited && node.tag == NodeTags::Visited){
            graph.drawables.at(node.id)->setColor(Color(0,0,255));
        }
    }
    if(displayPath){
        for (const auto& node : getPath()) {
            graph.drawables.at(node.id)->setColor(Color(0,255,0));
        }
    }

}}

std::unique_ptr<ISnapshot> Pathfinding::saveSnapshot() {
    auto snapshot = std::make_unique<Snapshot>();

    snapshot->target = &_target.get();
    snapshot->pathIsRegistered = _pathIsRegistered;
    snapshot->path = _path;
    snapshot->recalculatePathTime = _recalculatePathTime;
    snapshot->countedFrames = _countedFrames;

    return snapshot;
}

void Pathfinding::loadSnapshot(const ISnapshot& rawSnapshot) {
    auto& snapshot = (Snapshot&)rawSnapshot;

    _target = *snapshot.target;
    _pathIsRegistered = snapshot.pathIsRegistered;
    _path = snapshot.path;
    _recalculatePathTime = snapshot.recalculatePathTime;
    _countedFrames = snapshot.countedFrames;
}

Vector2 Pathfinding::getDirection(Vector2 target) {
    Vector2 newDir;

    //set new direction
    if(target.x < getParentGameObjectPosition().x && target.y == getParentGameObjectPosition().y){ // left
        newDir = Vector2(-1.0f, 0.0f);
    }else if(target.x > getParentGameObjectPosition().x && target.y == getParentGameObjectPosition().y){ // right
        newDir = Vector2(1.0f, 0.0f);
    }else if(target.y < getParentGameObjectPosition().y && target.x == getParentGameObjectPosition().x){ // up
        newDir = Vector2(0.0f, -1.0f);
    }else if(target.y > getParentGameObjectPosition().y && target.x == getParentGameObjectPosition().x){ // down
        newDir = Vector2(0.0f, 1.0f);
    }else if(target.x < getParentGameObjectPosition().x && target.y < getParentGameObjectPosition().y){ // leftUp
        newDir = Vector2(-1.0f, -1.0f);
    }else if(target.x < getParentGameObjectPosition().x && target.y > getParentGameObjectPosition().y){ // leftDown
        newDir = Vector2(-1.0f, 1.0f);
    }else if(target.x > getParentGameObjectPosition().x && target.y < getParentGameObjectPosition().y){ // rightUp
        newDir = Vector2(1.0f, -1.0f);
    }else if(target.x > getParentGameObjectPosition().x && target.y > getParentGameObjectPosition().y){ // rightDown
        newDir = Vector2(1.0f, 1.0f);
    }

    return newDir.normalized();;
}



