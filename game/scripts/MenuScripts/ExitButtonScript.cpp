//
// Created by olafv on 12/14/2022.
//

#include "ExitButtonScript.h"
#include "Core/GameLoop.h"
#include "Scene/GameObjects/UIObject/Button.h"

using namespace GolfEngine::Scene::UI;

void ExitButtonScript::onUpdate() {

    auto& sceneManager = GolfEngine::Core::SceneManager::GetSceneManager();

    auto& btn = getParentGameObject<Button>();

    if(btn.isClicked()){ //if button clicked
        GolfEngine::Core::getRunningGameLoop().stop();
    }
}
