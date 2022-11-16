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

Scene::Scene(const Scene& other) {
    _rootGameObject = nullptr;

    // Copy root GameObject
    // Copy constructor of GameObject will copy its children and in turn the entire scene
    _rootGameObject = new GameObject(*other._rootGameObject);
}

Scene& Scene::operator=(const Scene& other) {
    if(this != &other){
        // Delete existing root GameObject
        delete _rootGameObject;

        // Copy root GameObject
        // Copy constructor of GameObject will copy its children and in turn the entire scene
        _rootGameObject = new GameObject(*other._rootGameObject);
    }
    return *this;
}

//Scene::Scene(Scene&& other) {
//
//}
//
//Scene& Scene::operator=(Scene&& other) {
//    if(this != &other){
//
//    }
//    return *this;
//}

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
