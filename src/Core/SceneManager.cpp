//
// Created by Lucas on 2-11-2022.
//

#include "SceneManager.h"

void SceneManager::changeScene(const Scene& scene) {
    currentScene = scene;
}

void SceneManager::addScene(const Scene& scene) {
    scenes.emplace_back(scene);
}

Scene& SceneManager::getCurrentScene() {
    return currentScene;
}
