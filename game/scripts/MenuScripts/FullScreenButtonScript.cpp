//
// Created by olafv on 12/14/2022.
//

#include "FullScreenButtonScript.h"
#include "Core/GameLoop.h"
#include "Scene/GameObjects/UIObject/Button.h"
#include "Services/Singletons/RenderSingleton.h"

void FullScreenButtonScript::onUpdate() {

    auto& sceneManager = GolfEngine::SceneManager::GetSceneManager();
    auto* rs = GolfEngine::Services::Render::getService();

    //get range of button area to check if we clicked there
    auto& btn = getParentGameObject<Button>();

    if(btn.isClicked()){
        GolfEngine::Services::Render::getService()->setFullScreen(!rs->fullScreen());
        sceneManager.loadScene("settings");
    }
}
