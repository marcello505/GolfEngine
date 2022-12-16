//
// Created by olafv on 12/14/2022.
//

#include "ExitButtonScript.h"
#include "Core/GameLoop.h"
#include "Scene/GameObjects/UIObject/Button.h"

void ExitButtonScript::onUpdate() {

    auto& sceneManager = GolfEngine::SceneManager::GetSceneManager();

    //get range of button area to check if we clicked there
    auto& btn = getParentGameObject<Button>();

    if(btn.isClicked()){
        exit(0);
    }
}
