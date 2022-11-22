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
    for(auto& go : _gameObjects)
        if(go->getActive())
            go->onUpdate();
}

void Scene::startRecording(const std::string& actionToLock){}
void Scene::stopRecording(){}
void Scene::playRecording(){}

GameObject& Scene::getRootGameObject() const{
    return _rootGameObject->get();
}

