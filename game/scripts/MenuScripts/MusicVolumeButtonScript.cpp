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

    if(btn.isClicked()){ //if button is clicked
        if(btn._text.value == "-"){
            _audioService->setMusicVolume( _audioService->getMusicVolume() - 0.05f); //lower music volume
            int volumeNumber = GolfEngine::Utilities::Math::roundToNearestMultiple(_audioService->getMusicVolume() * 100, 5);
            _textUpdateScript->SetNewText(std::to_string(volumeNumber));
        } else {
            _audioService->setMusicVolume( _audioService->getMusicVolume() + 0.05f); //higher music volume
            int volumeNumber = GolfEngine::Utilities::Math::roundToNearestMultiple(_audioService->getMusicVolume() * 100, 5);
            _textUpdateScript->SetNewText(std::to_string(volumeNumber));
        }
    }
}