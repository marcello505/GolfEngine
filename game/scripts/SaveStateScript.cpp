//
// Created by marcello on 12/6/22.
//

#include <Core/SceneManager.h>
#include "SaveStateScript.h"

using namespace GolfEngine;

void SaveStateScript::onUpdate() {
    if(GolfEngine::Core::SceneManager::GetSceneManager().hasCurrentScene()){
        auto& currentScene = GolfEngine::Core::SceneManager::GetSceneManager().getCurrentScene();
        if(_actionMap->isJustPressed("startRecordingReplay")){
            std::vector<std::string> actionsToLock {
                "playerLeft",
                "playerRight",
                "playerUp",
                "playerDown",
                "playerShoot"
            };
            currentScene.startRecordingReplay(actionsToLock, true);
        }
        if(_actionMap->isJustPressed("stopRecordingReplay")){
            currentScene.stopRecordingReplay();
        }
        if(_actionMap->isJustPressed("playReplay")){
            currentScene.playReplay();
        }
    }
}

void SaveStateScript::onStart() {
    _actionMap = Input::ActionMap::getActionMap();
}
