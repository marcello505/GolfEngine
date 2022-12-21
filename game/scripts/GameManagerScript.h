//
// Created by conner on 12/13/2022.
//

#ifndef GOLFENGINE_GAMEMANAGERSCRIPT_H
#define GOLFENGINE_GAMEMANAGERSCRIPT_H

#include <utility>

#include "Scene/Components/BehaviourScript.h"

using namespace GolfEngine::Scene::Components;

class GameManagerScript : public BehaviourScript {
public:
    explicit GameManagerScript(std::string nextLevelName) : _nextLevelName{std::move(nextLevelName)} {}

    void restartLevel();
    void tryFinishLevel();

    [[nodiscard]] float getTimePassed() const;
    [[nodiscard]] float getHighScoreTime() const;
    bool isWaitingForQuitConfirmation() const;
    bool isLevelFinished() const;

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

    // Next level logic
    bool _levelFinished {false};
    const std::string _nextLevelName;
};


#endif //GOLFENGINE_GAMEMANAGERSCRIPT_H
