//
// Created by Lucas on 2-11-2022.
//

#ifndef SPC_PROJECT_SCENEMANAGER_H
#define SPC_PROJECT_SCENEMANAGER_H


#include <vector>
#include "../Scene/Scene.h"

class SceneManager {
private:
    std::vector<Scene> _scenes;
    Scene _currentScene;
public:
    /// Sets currentScene with as copy from list _scenes
    /// \param scene
    void changeScene(const Scene& scene);

    /// Adds scene to list of _scenes
    /// \param scene
    void addScene(const Scene& scene);

    /// Returns reference to _currentScene
    /// \return
    Scene& getCurrentScene();

    /// Returns vector of _scenes
    /// \return
    std::vector<Scene> getScenes() const;

    /// Delets SCene from _scene based on iterator
    /// \tparam It
    /// \param iterator
    template <class It>
    void deleteScene(It iterator){
        _scenes.erase(iterator);
    }

};


#endif //SPC_PROJECT_SCENEMANAGER_H
