//
// Created by marcello on 12/6/22.
//

#include <Core/SceneManager.h>
#include "SaveStateScript.h"

void SaveStateScript::onUpdate() {
    if(GolfEngine::SceneManager::GetSceneManager().hasCurrentScene()){
        if(_actionMap->isJustPressed("saveState")){
            GolfEngine::SceneManager::GetSceneManager().getCurrentScene().saveState();
        }
        if(_actionMap->isJustPressed("loadState")){
            GolfEngine::SceneManager::GetSceneManager().getCurrentScene().loadState();
        }
    }
}

void SaveStateScript::onStart() {
    _actionMap = ActionMap::getActionMap();
}
