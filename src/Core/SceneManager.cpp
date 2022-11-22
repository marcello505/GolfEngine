//
// Created by Lucas on 2-11-2022.
//

#include "SceneManager.h"

namespace GolfEngine {
    std::unique_ptr<SceneManager> SceneManager::sceneManager = nullptr;

    SceneManager::SceneManager() : _currentScene{nullptr} {
    }

    SceneManager& SceneManager::GetSceneManager() {
        if(sceneManager == nullptr)
            sceneManager.reset(new SceneManager());
        return *sceneManager;
    }

    void SceneManager::loadScene(const std::string& sceneName) {
        std::_Rb_tree_iterator<std::pair<const std::basic_string<char>, std::unique_ptr<ISceneFactory>>> sceneFactory;
        // If empty string is passed, reload last loaded scene
        if(sceneName.empty())
            sceneFactory = _scenes.find(_lastScene);
        else
            sceneFactory = _scenes.find(sceneName);

        if (sceneFactory != _scenes.end()){
            _lastScene = sceneName;
            _currentScene = std::make_unique<Scene>();
            sceneFactory->second->build(*_currentScene);
            _currentScene->startScene();
        }
    }

    Scene& SceneManager::getCurrentScene() {
        return *_currentScene;
    }

    void SceneManager::deleteScene(const std::string& sceneName) {
        auto sceneIt = _scenes.find(sceneName);
        if (sceneIt != _scenes.end())
            _scenes.erase(sceneIt);
    }

    bool SceneManager::hasCurrentScene() {
        return _currentScene != nullptr;
    }
}