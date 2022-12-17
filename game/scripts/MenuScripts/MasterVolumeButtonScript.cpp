//
// Created by olafv on 12/14/2022.
//

#include "MasterVolumeButtonScript.h"

#include "Utilities/Math.h"
#include "Core/GameLoop.h"
#include "Scene/GameObjects/UIObject/Button.h"
#include "Services/Singletons/AudioSingleton.h"

void MasterVolumeButtonScript::onUpdate() {

    auto& sceneManager = GolfEngine::SceneManager::GetSceneManager();
    auto* _audioService = GolfEngine::Services::Audio::getService();

    auto& btn = getParentGameObject<Button>();
//    ((number + multiple/2) / multiple) * multiple

    if(btn.isClicked()){ //if button is clicked
        if(btn._text.value == "-"){  //if button is meant for minus
            _audioService->setMasterVolume( _audioService->getMasterVolume() - 0.05f); //lower master volume
            int volumeNumber = GolfEngine::Utilities::Math::roundToNearestMultiple(_audioService->getMasterVolume() * 100, 5);
            _textUpdateScript->SetNewText(std::to_string(volumeNumber));
        } else {
            _audioService->setMasterVolume( _audioService->getMasterVolume() + 0.05f); //higher master volume
            int volumeNumber = GolfEngine::Utilities::Math::roundToNearestMultiple(_audioService->getMasterVolume() * 100, 5);
            _textUpdateScript->SetNewText(std::to_string(volumeNumber));
        }

    }
}