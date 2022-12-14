//
// Created by olafv on 12/14/2022.
//

#include "VolumeButtonScript.h"
#include "Core/GameLoop.h"
#include "Scene/GameObjects/UIObject/Button.h"
#include "Services/Singletons/AudioSingleton.h"

void VolumeButtonScript::onUpdate() {

    auto& sceneManager = GolfEngine::SceneManager::GetSceneManager();
    auto* _audioService = GolfEngine::Services::Audio::getService();

    auto& btn = getParentGameObject<Button>();

    if(btn.isClicked()){
        if(btn._text.value == "-"){
            _audioService->setMasterVolume( _audioService->getMasterVolume() - 0.1f);
        } else {
            _audioService->setMasterVolume( _audioService->getMasterVolume() + 0.1f);
        }

    }
}