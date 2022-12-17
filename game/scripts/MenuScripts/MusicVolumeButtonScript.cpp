//
// Created by olafv on 12/15/2022.
//

#include "MusicVolumeButtonScript.h"

#include "MusicVolumeButtonScript.h"
#include "Core/GameLoop.h"
#include "Scene/GameObjects/UIObject/Button.h"
#include "Services/Singletons/AudioSingleton.h"
#include "Core/Settings.h"

void MusicVolumeButtonScript::onUpdate() {

    auto& sceneManager = GolfEngine::SceneManager::GetSceneManager();
    auto* _audioService = GolfEngine::Services::Audio::getService();

    auto& btn = getParentGameObject<Button>();

    if(btn.isClicked()){ //if button is clicked
        float newVolume;
        if(btn._text.value == "-"){
            newVolume = _audioService->getMusicVolume() - 0.05f;
        } else {
            newVolume = _audioService->getMusicVolume() + 0.05f;
        }

        _audioService->setMusicVolume(newVolume); //lower music volume
        int volumeInPercent = GolfEngine::Utilities::Math::roundToNearestMultiple(_audioService->getMusicVolume() * 100, 5);
        _textUpdateScript->SetNewText(std::to_string(volumeInPercent));

        // Update project settings
        GolfEngine::Core::getProjectSettings().setFloat("MusicVolume", newVolume);
    }
}
