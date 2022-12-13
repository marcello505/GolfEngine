//
// Created by marcello on 12/13/22.
//
#include "Input/ActionMap.h"
#include "Utilities/IO.h"

#include "SaveGameTestScript.h"

#define SAVE_GAME_PATH "saveGameTest.xml"

void SaveGameTestScript::onUpdate() {
    auto& actionMap = *ActionMap::getActionMap();

    if(actionMap.isJustPressed("saveGame")){
        GolfEngine::Core::Settings save {};
        auto playerTransform = _player->getParentGameObject()->getWorldTransform();
        save.setFloat("player_pos_x", playerTransform.position.x);
        save.setFloat("player_pos_y", playerTransform.position.y);
        save.setFloat("player_rotation", playerTransform.rotation);
        save.setFloat("player_scale_x", playerTransform.scale.x);
        save.setFloat("player_scale_y", playerTransform.scale.y);
        GolfEngine::Utilities::IO::saveSettings(SAVE_GAME_PATH, save);
    }
    else if(actionMap.isJustPressed("loadGame")){
        if(GolfEngine::Utilities::IO::userDataFileExists(SAVE_GAME_PATH)){
            auto save = GolfEngine::Utilities::IO::loadSettings(SAVE_GAME_PATH);
            Transform playerTransform {};
            playerTransform.position.x = save.getFloat("player_pos_x");
            playerTransform.position.y = save.getFloat("player_pos_y");
            playerTransform.rotation = save.getFloat("player_rotation");
            playerTransform.scale.x = save.getFloat("player_scale_x");
            playerTransform.scale.y = save.getFloat("player_scale_y");
            _player->setTransform(playerTransform);
        }
    }
}
