//
// Created by olafv on 12/12/2022.
//

#include "Core/GameLoop.h"
#include "StartGameButtonScript.h"
#include "Scene/GameObjects/UIObject/Button.h"


void StartGameButtonScript::onUpdate() {

    auto& sceneManager = GolfEngine::SceneManager::GetSceneManager();

    //get range of button area to check if we clicked there
    auto& btn = getParentGameObject<Button>();

    if(btn.isClicked()){ //if button is clicked
        if(btn._text.value == "Start game"){
            sceneManager.loadScene("level1");
        } else if(btn._text.value == "1") {
            sceneManager.loadScene("level1");
        }
        else if(btn._text.value == "2") {
            sceneManager.loadScene("level2");
        }
        else if(btn._text.value == "3") {
            sceneManager.loadScene("level3");
        }

    }
}

