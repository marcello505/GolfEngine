//
// Created by Lucas on 2-11-2022.
//

#include "SceneManager.h"

void SceneManager::changeScene(const Scene& scene) {
    _currentScene = scene;
}

void SceneManager::addScene(const Scene& scene) {
    _scenes.emplace_back(scene);
}

Scene& SceneManager::getCurrentScene() {
    return _currentScene;
}

std::vector<Scene> SceneManager::getScenes() const {
    return _scenes;
}