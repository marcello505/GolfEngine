//
// Created by olafv on 12/14/2022.
//

#include "Core/GameLoop.h"
#include "BackButtonScript.h"
#include "Scene/GameObjects/UIObject/Button.h"

void BackButtonScript::onUpdate() {

    auto& sceneManager = GolfEngine::SceneManager::GetSceneManager();

    auto& btn = getParentGameObject<Button>();

    if(btn.isClicked()){ //if button is clicked
        sceneManager.loadScene("mainMenu"); //go to main menu
    }
}
