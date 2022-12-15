//
// Created by olafv on 12/15/2022.
//

#include "KeyConfigButtonScript.h"
#include "Core/GameLoop.h"
#include "Scene/GameObjects/UIObject/Button.h"
#include "Services/Singletons/InputSingleton.h"

void KeyConfigButtonScript::onUpdate() {

    auto& sceneManager = GolfEngine::SceneManager::GetSceneManager();
    auto* inputService = GolfEngine::Services::Input::getService();

    //get range of button area to check if we clicked there
    auto& btn = getParentGameObject<Button>();


    if(btn.isClicked()){
     /*   sceneManager.loadScene("keyConfig");*/
        InputKey newKey;
        while (!(inputService->pressedKey()))
        {
            newKey = inputService->getKeyPressed();
        }
        inputService->setKeyPressed(false);
        ActionMap::getActionMap()->addInputKeyToAction(_actionName, newKey);
/*        sceneManager.loadScene("settings");*/
/*        showingKeyConfigScene = false;
        showingKeyConfigScene = true;*/
    }

}
