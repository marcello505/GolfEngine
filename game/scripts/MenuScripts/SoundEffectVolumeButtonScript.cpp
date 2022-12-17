//
// Created by olafv on 12/15/2022.
//

#include "SoundEffectVolumeButtonScript.h"
#include "Core/GameLoop.h"
#include "Scene/GameObjects/UIObject/Button.h"
#include "Services/Singletons/AudioSingleton.h"

void SoundEffectVolumeButtonScript::onUpdate() {

    auto& sceneManager = GolfEngine::SceneManager::GetSceneManager();
    auto* _audioService = GolfEngine::Services::Audio::getService();

    auto& btn = getParentGameObject<Button>();

    if(btn.isClicked()){
        if(btn._text.value == "-"){ //if button is clicked
            _audioService->setSfxVolume( _audioService->getSfxVolume() - 0.05f); //lower sfx volume
            int volumeNumber = GolfEngine::Utilities::Math::roundToNearestMultiple(_audioService->getSfxVolume() * 100, 5);
            _textUpdateScript->SetNewText(std::to_string(volumeNumber));
        } else {
            _audioService->setSfxVolume( _audioService->getSfxVolume() + 0.05f); //higher sfx volume
            int volumeNumber = GolfEngine::Utilities::Math::roundToNearestMultiple(_audioService->getSfxVolume() * 100, 5);
            _textUpdateScript->SetNewText(std::to_string(volumeNumber));
        }

    }
}