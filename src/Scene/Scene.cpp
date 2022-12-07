//
// Created by conner on 11/21/2022.
//

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

    //Save Recording starting state
    if(_saveReplayState){
        _saveReplayState = false;

        saveCurrentState(std::ref(_replay.value().startingState));
    }
}

void Scene::startRecordingReplay(const std::vector<std::string>& actionsToLock){
    _isRecordingReplay = true;
    _saveReplayState = true;
    _replay = Replay{};
    _replay.value().lockedActions = actionsToLock;
}

void Scene::stopRecordingReplay(){
    _isRecordingReplay = false;
}
void Scene::playReplay(){}

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

void Scene::updateReplay() {
    //Record inputs for recording
    if(_isRecordingReplay){
        auto& actionMap = *ActionMap::getActionMap();
        std::vector<bool> actionsSnapshots {};

        for(auto& actionToLock : _replay.value().lockedActions){
            actionsSnapshots.emplace_back(actionMap.isPressed(actionToLock));
        }

        _replay.value().inputs.push_back(actionsSnapshots);
    }

}

