//
// Created by Lucas on 2-11-2022.
//

#ifndef SPC_PROJECT_SCENEMANAGER_H
#define SPC_PROJECT_SCENEMANAGER_H

#include <map>
#include "../Scene/Scene.h"
#include <memory>
#include "../Scene/ISceneFactory.h"

class ISceneFactory;

namespace GolfEngine {

class SceneManager {
private:
    std::map<std::string, std::unique_ptr<ISceneFactory>> _scenes;
    std::unique_ptr<Scene> _currentScene;
    std::string _lastScene;

    static std::unique_ptr<SceneManager> sceneManager;

    SceneManager();
public:
    /// This method is used to get access to the scene manager instance
    /// \return Returns the global scene manager instance
    static SceneManager& GetSceneManager();

    /// Loads new scene by setting the currentScene of a copy of the loaded scene
    /// \param sceneName Name of scene to load, if empty, current scene will be reloaded
    void loadScene(const std::string &sceneName = "");

    /// Adds a Scene Factory to the SceneManager, which can create new scenes on command using the loadScene method
    /// \tparam SF Scene Factory type
    /// \param sceneName Name of the scene this factory creates
    template<typename SF>
    void addSceneFactory(const std::string& sceneName){
        _scenes.insert(std::make_pair(sceneName, std::make_unique<SF>()));
    }

    /// Returns reference to _currentScene
    /// \return
    Scene& getCurrentScene();

    /// Checks if there is an active scene
    /// \return true if a scene is active
    bool hasCurrentScene();

    /// Clears the scenes map by deleting factories
    void clearScenes();

    /// Adds a scene to the scene list
    /// \param sceneName Name of the scene
    /// \param newScene Pointer reference to the scene object
    template<typename S>
    void addScene(const std::string& sceneName) {
        _scenes.insert({sceneName, std::make_unique<S>()});
    }
};

}

#endif //SPC_PROJECT_SCENEMANAGER_H
