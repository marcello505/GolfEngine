//
// Created by olafv on 12/14/2022.
//

#include "ExitButtonScript.h"
#include "Core/GameLoop.h"
#include "Scene/GameObjects/UIObject/Button.h"

void ExitButtonScript::onUpdate() {

    auto& sceneManager = GolfEngine::SceneManager::GetSceneManager();

    auto& btn = getParentGameObject<Button>();

    if(btn.isClicked()){ //if button clicked
        exit(0); //exit application
    }
}
