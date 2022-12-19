//
// Created by olafv on 12/12/2022.
//

#include "Core/GameLoop.h"
#include "StartGameButtonScript.h"
#include "Scene/GameObjects/UIObject/Button.h"

using namespace GolfEngine::Scene::UI;

void StartGameButtonScript::onUpdate() {

    auto& sceneManager = GolfEngine::Core::SceneManager::GetSceneManager();

    //get range of button area to check if we clicked there
    auto& btn = getParentGameObject<Button>();

    if(btn.isClicked()){ //if button is clicked
        sceneManager.loadScene(btn.name); //load playerTest scene
    }
}

