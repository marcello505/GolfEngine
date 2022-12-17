//
// Created by olafv on 12/14/2022.
//

#include "Core/GameLoop.h"
#include "SettingsButtonScript.h"
#include "Scene/GameObjects/UIObject/Button.h"

void SettingsButtonScript::onUpdate() {

    auto& sceneManager = GolfEngine::SceneManager::GetSceneManager();

    //get range of button area to check if we clicked there
    auto& btn = getParentGameObject<Button>();

    if(btn.isClicked()){ //if button is clicked
        sceneManager.loadScene("settings"); //loadscene
    }
}