//
// Created by marce on 02/11/2022.
//

#include "Scene.h"

void Scene::startRecording(const std::string& actionToLock){};
void Scene::stopRecording(){};
void Scene::playRecording(){}

void Scene::setRootGameObject(const GameObject& gameObject) {
    _rootGameObject = gameObject;
};
GameObject& Scene::getRootGameObject() {
    return _rootGameObject;
};