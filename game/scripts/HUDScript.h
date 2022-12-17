//
// Created by conner on 12/15/2022.
//

#ifndef GOLFENGINE_HUDSCRIPT_H
#define GOLFENGINE_HUDSCRIPT_H

#include <Scene/Components/BehaviourScript.h>
#include <Scene/GameObjects/UIObject/Text.h>
#include "GameManagerScript.h"

class HUDScript : public BehaviourScript {
public:
    HUDScript(Text* fpsText, Text* timeText, Text* highScoreTimeText, Text* quitConfirmationText, Text* levelCompleteText);
    void onStart() override;
    void onUpdate() override;
private:
    Text* _fpsText, *_timeText, *_highScoreTimeText, *_quitConfirmationText, *_levelCompleteText;
    GameManagerScript* _gameManager;
    bool _renderFPS;

    void updateHighScoreText();
};


#endif //GOLFENGINE_HUDSCRIPT_H
