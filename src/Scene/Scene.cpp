//
// Created by conner on 11/21/2022.
//

#include <iostream>

#include "Scene.h"
#include "GameObjects/GameObject.h"
#include "Input/ActionMap.h"

Scene::Scene() {
    _gameObjects.push_back(std::make_unique<GameObject>());
    _rootGameObject = std::make_unique<std::reference_wrapper<GameObject>>(*_gameObjects.back());
}

void Scene::startScene() {
    for(auto& go : _gameObjects)
        if(go->getActive())
            go->onStart();
}

void Scene::updateScene() {
    //Load state (if requested)
    if(_loadStateCalled){
        _loadStateCalled = false;

        for(int i = 0; i < _savedState.size(); ++i){
            _gameObjects[i]->loadSnapshot(*_savedState[i]);
        }
    }


    //Update scene
    for(auto& go : _gameObjects)
        if(go->getActive())
            go->onUpdate();

    //Save state (if requested)
    if(_saveStateCalled){
        _saveStateCalled = false;

        saveCurrentState(std::ref(_savedState));
    }
}

void Scene::startRecordingReplay(const std::vector<std::string>& actionsToLock, bool recordMouse) {
    _replayState = ReplayState::InitializeRecording;
    _replay = Replay{};
    _replay.lockedActions = actionsToLock;
    //If recordMouse is true, initialize the list
    if(recordMouse) _replay.mousePositions = std::vector<std::pair<int, int>>{};
}

void Scene::stopRecordingReplay(){
    _replayState = ReplayState::Idle;
}
void Scene::playReplay(){
    _replayState = ReplayState::InitializePlaying;
}

GameObject& Scene::getRootGameObject() const{
    return _rootGameObject->get();
}

void Scene::saveState() {
    _saveStateCalled = true;
}

void Scene::loadState() {
    _loadStateCalled = true;
}

void Scene::saveCurrentState(std::vector<std::unique_ptr<ISnapshot>>& list) {
    list.clear();
    for(int i = 0; i < _gameObjects.size(); ++i){
        list.push_back(_gameObjects[i]->saveSnapshot());
    }
}

void Scene::loadCurrentState(std::vector<std::unique_ptr<ISnapshot>>& list) {
    for(int i = 0; i < list.size(); ++i){
        _gameObjects[i]->loadSnapshot(*list[i]);
    }
}

void Scene::updateReplay() {
    switch(_replayState){
        //Save current state in replay
        case ReplayState::InitializeRecording:{
            _replayState = ReplayState::Recording;
            saveCurrentState(std::ref(_replay.startingState));
        }

        //Record inputs for replay
        case ReplayState::Recording:{
            auto& actionMap = *ActionMap::getActionMap();
            std::vector<std::pair<bool, bool>> actionsSnapshots {};

            for(auto& actionToLock : _replay.lockedActions){
                actionsSnapshots.emplace_back(actionMap.isPressed(actionToLock), actionMap.isJustPressed(actionToLock));
            }

            if(_replay.mousePositions){
                auto mousePosition = actionMap.getMousePosition();
                _replay.mousePositions.value().emplace_back(mousePosition.x, mousePosition.y);
            }

            _replay.inputs.push_back(actionsSnapshots);
            break;
        }

        //Load state from replay
        case ReplayState::InitializePlaying:{
            _replayState = ReplayState::Playing;
            loadCurrentState(std::ref(_replay.startingState));
            _replayFrame = 0;
        }

        //Load inputs from replay
        case ReplayState::Playing:{
            std::cout << "Playing frame: " << _replayFrame << std::endl;
            //Check if at the end of the replay
            if(_replayFrame >= _replay.inputs.size()){
                _replayState = ReplayState::Idle;
                break;
            }

            auto& actionMap = *ActionMap::getActionMap();

            //Get inputs of the current frame and then set them
            auto& inputs = _replay.inputs[_replayFrame];
            for(int i = 0; i < inputs.size(); ++i){
                actionMap.setActionPressed(_replay.lockedActions[i], inputs[i].first, inputs[i].second);
            }

            if(_replay.mousePositions){
                auto& mousePos = _replay.mousePositions->at(_replayFrame);
                actionMap.setMousePosition(mousePos.first, mousePos.second);
            }

            //Increase replayFrame
            _replayFrame++;
            break;
        }
        case ReplayState::Idle:
            break;
    }

}


