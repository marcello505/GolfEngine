//
// Created by olafv on 12/14/2022.
//

#include "MasterVolumeButtonScript.h"

#include "Utilities/Math.h"
#include "Core/GameLoop.h"
#include "Scene/GameObjects/UIObject/Button.h"
#include "Services/Singletons/AudioSingleton.h"
#include "Core/Settings.h"

void MasterVolumeButtonScript::onUpdate() {

    auto& sceneManager = GolfEngine::SceneManager::GetSceneManager();
    auto* _audioService = GolfEngine::Services::Audio::getService();

    auto& btn = getParentGameObject<Button>();

    if(btn.isClicked()){ //if button is clicked
        float newVolume;
        if(btn._text.value == "-"){  //if button is meant for minus
            newVolume = _audioService->getMasterVolume() - 0.05f;
            if(newVolume < 0.0f)
                newVolume = 0.0f;
        } else {
            newVolume = _audioService->getMasterVolume() + 0.05f;
            if(newVolume > 1.0f)
                newVolume = 1.0f;
        }

        // Update volume in Audio Service and update text
        _audioService->setMasterVolume( newVolume);
        int volumeInPercent = GolfEngine::Utilities::Math::roundToNearestMultiple(_audioService->getMasterVolume() * 100, 5);
        _textUpdateScript->SetNewText(std::to_string(volumeInPercent));

        // Update project settings
        GolfEngine::Core::getProjectSettings().setFloat("MasterVolume", newVolume);
    }
}
