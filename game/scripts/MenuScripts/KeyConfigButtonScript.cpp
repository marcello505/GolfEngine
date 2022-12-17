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

    if(btn.isClicked()){ //if button is clicked
        InputKey newKey;
        while(!inputService->pressedKey()){ // read key input
            newKey = inputService->getKeyPressed();
        }
        inputService->setKeyPressed(false); // setup available for next read
        actionMap->removeInputKeysFromAction(_actionName); //remove current input key bound to action
        actionMap->addInputKeyToAction(_actionName, newKey); //add new input key to action
        std::string playerInputKey = inputService->
                getKeyString(actionMap->getActionKeys(_actionName)[0]); // get first key from list (our game
                                                                                  // happens to bound
                                                                                  // only one key per action)

        _textUpdateScript->SetNewText(_actionName + " ( " + playerInputKey  + " )"); // show new key in ui
    }
}
