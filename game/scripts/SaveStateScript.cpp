//
// Created by marcello on 12/6/22.
//

#include <Core/SceneManager.h>
#include "SaveStateScript.h"

void SaveStateScript::onUpdate() {
    if(GolfEngine::SceneManager::GetSceneManager().hasCurrentScene()){
        auto& currentScene = GolfEngine::SceneManager::GetSceneManager().getCurrentScene();
        if(_actionMap->isJustPressed("saveState")){
            GolfEngine::SceneManager::GetSceneManager().getCurrentScene().saveState();
        }
        if(_actionMap->isJustPressed("loadState")){
            GolfEngine::SceneManager::GetSceneManager().getCurrentScene().loadState();
        }
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
    _actionMap = ActionMap::getActionMap();
}
