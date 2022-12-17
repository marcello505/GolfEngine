//
// Created by olafv on 12/14/2022.
//

#include "MasterVolumeButtonScript.h"

#include "Core/GameLoop.h"
#include "Scene/GameObjects/UIObject/Button.h"
#include "Services/Singletons/AudioSingleton.h"

void MasterVolumeButtonScript::onUpdate() {

    auto& sceneManager = GolfEngine::SceneManager::GetSceneManager();
    auto* _audioService = GolfEngine::Services::Audio::getService();

    auto& btn = getParentGameObject<Button>();

    if(btn.isClicked()){ //if button is clicked
        if(btn._text.value == "-"){  //if button is meant for minus
            _audioService->setMasterVolume( _audioService->getMasterVolume() - 0.1f); //lower master volume
            _textUpdateScript->SetNewText(std::to_string((int)(_audioService->getMasterVolume() *10) * 10));
        } else {
            _audioService->setMasterVolume( _audioService->getMasterVolume() + 0.1f); //higher master volume
            _textUpdateScript->SetNewText(std::to_string((int)(_audioService->getMasterVolume() *10) * 10));
        }

    }
}