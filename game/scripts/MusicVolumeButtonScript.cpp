//
// Created by olafv on 12/15/2022.
//

#include "MusicVolumeButtonScript.h"

#include "MusicVolumeButtonScript.h"
#include "Core/GameLoop.h"
#include "Scene/GameObjects/UIObject/Button.h"
#include "Services/Singletons/AudioSingleton.h"

void MusicVolumeButtonScript::onUpdate() {

    auto& sceneManager = GolfEngine::SceneManager::GetSceneManager();
    auto* _audioService = GolfEngine::Services::Audio::getService();

    auto& btn = getParentGameObject<Button>();

    if(btn.isClicked()){
        if(btn._text.value == "-"){
            _audioService->setMusicVolume( _audioService->getMusicVolume() - 0.1f);
            _textUpdateScript->SetNewText(std::to_string((int)(_audioService->getMusicVolume() *10) * 10));
        } else {
            _audioService->setMusicVolume( _audioService->getMusicVolume() + 0.1f);
            _textUpdateScript->SetNewText(std::to_string((int)(_audioService->getMusicVolume() *10) * 10));
        }
    }
}