//
// Created by Lucas on 2-11-2022.
//

#ifndef SPC_PROJECT_SCENEMANAGER_H
#define SPC_PROJECT_SCENEMANAGER_H


#include <vector>
#include "../Scene/Scene.h"

class SceneManager {
private:
    std::vector<Scene> scenes;
    Scene currentScene;
public:
    void changeScene(const Scene& scene);
    void addScene(const Scene& scene);
    Scene& getCurrentScene();

};


#endif //SPC_PROJECT_SCENEMANAGER_H