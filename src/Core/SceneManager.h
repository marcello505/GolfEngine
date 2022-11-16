//
// Created by Lucas on 2-11-2022.
//

#ifndef SPC_PROJECT_SCENEMANAGER_H
#define SPC_PROJECT_SCENEMANAGER_H

#include <map>
#include "../Scene/Scene.h"

namespace Core {

class SceneManager {
private:
    std::map<std::string, Scene *> _scenes;
    Scene *_currentScene;

    static SceneManager* sceneManager;

    SceneManager();
    ~SceneManager();
public:
    /// This method is used to get access to the scene manager instance
    /// \return Returns the global scene manager instance
    static SceneManager* GetSceneManager();

    /// Loads new scene by setting the currentScene of a copy of the loaded scene
    /// \param sceneName Name of scene to load
    void loadScene(const std::string &sceneName);

    /// Adds scene to list of _scenes
    /// \param sceneName Name of the new scene
    /// \param scene Pointer to the scene
    Scene *createScene(const std::string &sceneName);

    /// Returns reference to _currentScene
    /// \return
    Scene &getCurrentScene();

    /// Returns vector of _scenes
    /// \return
    std::vector<Scene *> getScenes();

    /// Deletes a scene from the scenes map
    /// \param sceneName Name of the scene to be deleted
    void deleteScene(const std::string &sceneName);
};

}

#endif //SPC_PROJECT_SCENEMANAGER_H
