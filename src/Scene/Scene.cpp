//
// Created by marce on 02/11/2022.
//

#include "Scene.h"

Scene::Scene() : _rootGameObject{nullptr} {
    _rootGameObject = new GameObject(this);
}

Scene::~Scene() {
    delete _rootGameObject;
}

void Scene::startRecording(const std::string& actionToLock){}
void Scene::stopRecording(){}
void Scene::playRecording(){}

void Scene::setRootGameObject(GameObject* gameObject) {
    _rootGameObject = gameObject;
}

GameObject* Scene::getRootGameObject() {
    return _rootGameObject;
}

void Scene::startScene() {
    _rootGameObject->onStart();
}

void Scene::updateScene() {
    _rootGameObject->onUpdate();
}
