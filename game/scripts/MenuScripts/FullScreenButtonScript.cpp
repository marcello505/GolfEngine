//
// Created by olafv on 12/14/2022.
//

#include "FullScreenButtonScript.h"
#include "Core/GameLoop.h"
#include "Scene/GameObjects/UIObject/Button.h"
#include "Services/Singletons/RenderSingleton.h"

using namespace GolfEngine::Scene::UI;

void FullScreenButtonScript::onUpdate() {

    auto& sceneManager = GolfEngine::Core::SceneManager::GetSceneManager();
    auto* rs = GolfEngine::Services::Render::getService();

    auto& btn = getParentGameObject<Button>();

    if(btn.isClicked()){ //if button is clicked
        GolfEngine::Services::Render::getService()->setFullScreen(!rs->fullScreen()); //toggle fullScreen
    }
}
