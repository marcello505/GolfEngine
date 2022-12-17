//
// Created by conner on 12/13/2022.
//

#ifndef GOLFENGINE_GAMEMANAGERSCRIPT_H
#define GOLFENGINE_GAMEMANAGERSCRIPT_H

#include "Scene/Components/BehaviourScript.h"

class GameManagerScript : public BehaviourScript {
public:
    void restartLevel();
    void tryFinishLevel();

    [[nodiscard]] float getTimePassed() const;
    [[nodiscard]] float getHighScoreTime() const;
    bool isWaitingForQuitConfirmation() const;

    void onStart() override;
    void onUpdate() override;
private:
    std::vector<std::string> _playerActionsToLock {"playerLeft",
                                                   "playerRight",
                                                   "playerUp",
                                                   "playerDown",
                                                   "playerShoot",
                                                   "playerReload"};

    void finishLevel();
    void startRecordingReplay();
    float _timePassed {0.0f};
    std::string _highScoreKey{};

    // Exit level logic
    bool _waitingForQuitConfirmation {false};
    float _quitConfirmationTimePassed {0.0f};
};


#endif //GOLFENGINE_GAMEMANAGERSCRIPT_H
