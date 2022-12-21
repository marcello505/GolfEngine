//
// Created by Lucas on 2-11-2022.
//

#include "Core/GameLoop.h"
#include "SceneManager.h"
#include "Services/Singletons/PathfindingSingleton.h"
#include "Services/Singletons/RenderSingleton.h"

namespace GolfEngine::Core{
    std::unique_ptr<SceneManager> SceneManager::sceneManager = nullptr;

    SceneManager::SceneManager() : _currentScene{nullptr} {
    }

    SceneManager& SceneManager::GetSceneManager() {
        if(sceneManager == nullptr)
            sceneManager.reset(new SceneManager());
        return *sceneManager;
    }

    void SceneManager::loadScene(const std::string& sceneName) {
        _nextScene = sceneName;
    }

    Scene::Scene& SceneManager::getCurrentScene() {
        return *_currentScene;
    }

    bool SceneManager::hasCurrentScene() {
        return _currentScene != nullptr;
    }

    void SceneManager::clearScenes() {
        _scenes.erase(_scenes.begin(), _scenes.end());
    }

    void SceneManager::updateSceneManager() {
        //Check if the current scene should be changed
        if(_nextScene){
            const auto& sceneName = _nextScene.value();
            std::_Rb_tree_iterator<std::pair<const std::basic_string<char>, std::unique_ptr<ISceneFactory>>> sceneFactory;
            // If empty string is passed, reload last loaded scene
            if(sceneName.empty())
                sceneFactory = _scenes.find(_lastScene);
            else
                sceneFactory = _scenes.find(sceneName);

            if (sceneFactory != _scenes.end()){
                _lastScene = sceneName;
                _currentScene = std::make_unique<Scene::Scene>();
                sceneFactory->second->build(*_currentScene);

                //Reset camera to empty
                if(GolfEngine::Services::Render::hasService()){
                    GolfEngine::Services::Render::getService()->setMainCamera({});
                }

                //Start Scene
                _currentScene->startScene();

                //Create new PathFinding Graph
                if(GolfEngine::Services::Pathfinding::hasService()){
                    GolfEngine::Services::Pathfinding::getService()->createGraph();
                }

                //Reset lag, meaning any late physics tics are reset
                if(GolfEngine::Core::hasRunningGameLoop())
                    GolfEngine::Core::getRunningGameLoop().resetLag();
            }
            _nextScene.reset();
        }

    }

    std::string SceneManager::getCurrentSceneName() const {
        return _lastScene;
    }
}
