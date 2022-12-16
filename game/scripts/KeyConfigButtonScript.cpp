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
    auto* actionMap = ActionMap::getActionMap();

    auto& btn = getParentGameObject<Button>();

    if(btn.isClicked()){
        btn._text.value ="reading..";
        InputKey newKey;
        while (!(inputService->pressedKey()))
        {
            newKey = inputService->getKeyPressed();
        }
        inputService->setKeyPressed(false);
        actionMap->removeInputKeyFromAction(_actionName);
        actionMap->addInputKeyToAction(_actionName, newKey);
        std::string playerInputKey = inputService->getKeyString(actionMap->getActionKeys(_actionName)[0]);
        _textUpdateScript->SetNewText(_actionName + " ( " + playerInputKey  + " )");
    }
}
