//
// Created by Lucas on 2-11-2022.
//

#ifndef SPC_PROJECT_SCENEMANAGER_H
#define SPC_PROJECT_SCENEMANAGER_H

#include <map>
#include <memory>
#include <optional>

#include "../Scene/Scene.h"
#include "../Scene/ISceneFactory.h"

class ISceneFactory;

namespace GolfEngine {

class SceneManager {
private:
    std::map<std::string, std::unique_ptr<ISceneFactory>> _scenes;
    std::unique_ptr<Scene> _currentScene;
    std::string _lastScene;

    // If this has a value, then the next call to updateSceneManager() will change the scene to the string given
    std::optional<std::string> _nextScene {};

    static std::unique_ptr<SceneManager> sceneManager;

    SceneManager();
public:
    /// This method is used to get access to the scene manager instance
    /// \return Returns the global scene manager instance
    static SceneManager& GetSceneManager();

    /// A deferred call to load  a new scene by setting the currentScene of a copy of the loaded scene
    /// The actual loading happens on the next updateSceneManager() call
    /// \param sceneName Name of scene to load, if empty, current scene will be reloaded
    void loadScene(const std::string &sceneName = "");

    /// Adds a Scene Factory to the SceneManager, which can create new scenes on command using the loadScene method
    /// \tparam SF Scene Factory type
    /// \param sceneName Name of the scene this factory creates
    template<typename SF>
    void addSceneFactory(const std::string& sceneName){
        _scenes.insert(std::make_pair(sceneName, std::make_unique<SF>()));
    }

    /// Update the scene manager if needed, should be called by the GameLoop before updating the current scene.
    /// For now the only update action is loading in a new scene if _nextScene has a value
    void updateSceneManager();

    /// Returns reference to _currentScene
    /// \return
    Scene& getCurrentScene();

    /// Checks if there is an active scene
    /// \return true if a scene is active
    bool hasCurrentScene();

    /// Clears the scenes map by deleting factories
    void clearScenes();

    /// Returns the name of the scene that was last loaded
    /// \return name of the scene
    [[nodiscard]] std::string getCurrentSceneName() const;

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
