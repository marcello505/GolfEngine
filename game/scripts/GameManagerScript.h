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
};


#endif //GOLFENGINE_GAMEMANAGERSCRIPT_H
