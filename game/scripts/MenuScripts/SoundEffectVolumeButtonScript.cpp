//
// Created by olafv on 12/15/2022.
//

#include "SoundEffectVolumeButtonScript.h"
#include "Core/GameLoop.h"
#include "Scene/GameObjects/UIObject/Button.h"
#include "Services/Singletons/AudioSingleton.h"
#include "Core/Settings.h"

void SoundEffectVolumeButtonScript::onUpdate() {

    auto& sceneManager = GolfEngine::SceneManager::GetSceneManager();
    auto* _audioService = GolfEngine::Services::Audio::getService();

    auto& btn = getParentGameObject<Button>();

    if(btn.isClicked()){
        float newVolume;
        if(btn._text.value == "-"){ //if button is clicked
            newVolume = _audioService->getSfxVolume() - 0.05f;
        } else {
            newVolume = _audioService->getSfxVolume() + 0.05f;
        }

        _audioService->setSfxVolume(newVolume); //lower sfx volume
        int volumeInPercent = GolfEngine::Utilities::Math::roundToNearestMultiple(_audioService->getSfxVolume() * 100, 5);
        _textUpdateScript->SetNewText(std::to_string(volumeInPercent));

        // Update project settings
        GolfEngine::Core::getProjectSettings().setFloat("SFXVolume", newVolume);
    }
}
