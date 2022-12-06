//
// Created by conner on 11/21/2022.
//

#include "Scene.h"
#include "GameObjects/GameObject.h"

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

        _savedState.clear();
        for(auto& go : _gameObjects){
            _savedState.push_back(go->saveSnapshot());
        }
    }
}

void Scene::startRecording(const std::string& actionToLock){}
void Scene::stopRecording(){}
void Scene::playRecording(){}

GameObject& Scene::getRootGameObject() const{
    return _rootGameObject->get();
}

void Scene::saveState() {
    _saveStateCalled = true;
}

void Scene::loadState() {
    _loadStateCalled = true;
}

