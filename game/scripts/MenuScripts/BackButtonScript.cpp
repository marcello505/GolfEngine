//
// Created by olafv on 12/14/2022.
//

#include "Core/GameLoop.h"
#include "BackButtonScript.h"
#include "Scene/GameObjects/UIObject/Button.h"

using namespace GolfEngine::Scene::UI;

void BackButtonScript::onUpdate() {

    auto& sceneManager = GolfEngine::Core::SceneManager::GetSceneManager();

    auto& btn = getParentGameObject<Button>();

    if(btn.isClicked()){ //if button is clicked
        sceneManager.loadScene("mainMenu"); //go to main menu
    }
}
