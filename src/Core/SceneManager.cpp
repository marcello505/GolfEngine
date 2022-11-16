//
// Created by Lucas on 2-11-2022.
//

#include "SceneManager.h"

namespace Core {
    SceneManager* SceneManager::sceneManager = nullptr;

    SceneManager::SceneManager() : _currentScene{nullptr}, _scenes{}{
    }

    SceneManager* SceneManager::GetSceneManager() {
        if(sceneManager == nullptr)
            sceneManager = new SceneManager();
        return sceneManager;
    }

    void SceneManager::loadScene(const std::string& sceneName) {
        auto sceneIt = _scenes.find(sceneName);
        if (sceneIt != _scenes.end())
            _currentScene = new Scene(*sceneIt->second);
        // TODO maybe throw exception for not finding the scene?
    }

    Scene *SceneManager::createScene(const std::string &sceneName) {
        auto newScene = new Scene{};
        _scenes.insert({sceneName, newScene});
        return newScene;
    }

    Scene &SceneManager::getCurrentScene() {
        return *_currentScene;
    }

    std::vector<Scene *> SceneManager::getScenes() {
        std::vector<Scene *> scenes;
        for (auto &scene: _scenes)
            scenes.push_back(scene.second);
        return std::move(scenes);
    }

    void SceneManager::deleteScene(const std::string &sceneName) {
        auto sceneIt = _scenes.find(sceneName);
        if (sceneIt != _scenes.end())
            _scenes.erase(sceneIt);
    }

}