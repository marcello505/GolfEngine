//
// Created by marce on 02/11/2022.
//

#include "Scene.h"

Scene::Scene() : _rootGameObject{nullptr} {
    _rootGameObject = std::make_unique<GameObject>();
}

Scene::Scene(const Scene& other) {
    _rootGameObject.reset();

    // Copy root GameObject
    // Copy constructor of GameObject will copy its children and in turn the entire scene
    _rootGameObject = std::make_unique<GameObject>(*other._rootGameObject);
}

Scene& Scene::operator=(const Scene& other) {
    if(this != &other){
        // Delete existing root GameObject
        _rootGameObject.reset();

        // Copy root GameObject
        // Copy constructor of GameObject will copy its children and in turn the entire scene
        _rootGameObject = std::make_unique<GameObject>(*other._rootGameObject);
    }
    return *this;
}

void Scene::startRecording(const std::string& actionToLock){}
void Scene::stopRecording(){}
void Scene::playRecording(){}

void Scene::setRootGameObject(GameObject* gameObject) {
    _rootGameObject.reset(gameObject);
}

GameObject* Scene::getRootGameObject() {
    return _rootGameObject.get();
}

void Scene::startScene() {
    _rootGameObject->onStart();
}

void Scene::updateScene() {
    _rootGameObject->onUpdate();
}

GameObject* Scene::createGameObject(GameObject& gameObject, GameObject* parent) {
    GameObject* newGameObject{nullptr};

    // Create gameObject under the given parent, if no parent is given, create new GameObject under the root GameObject
    if(parent)
        newGameObject = parent->createChildGameObject(gameObject);
    else
        newGameObject = _rootGameObject->createChildGameObject(gameObject);

    return newGameObject;
}

GameObject* Scene::createGameObject(GameObject* gameObject, GameObject* parent) {
    GameObject* newGameObject{nullptr};

    // Create gameObject under the given parent, if no parent is given, create new GameObject under the root GameObject
    if(parent)
        newGameObject = parent->createChildGameObject(gameObject);
    else
        newGameObject = _rootGameObject->createChildGameObject(gameObject);

    return newGameObject;
}
