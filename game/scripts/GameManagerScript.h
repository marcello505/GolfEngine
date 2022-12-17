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
private:
    void onStart() override;
    void onUpdate() override;
    void finishLevel();
private:
    float _timePassed {0.0f};
    std::string _highScoreKey{};
};


#endif //GOLFENGINE_GAMEMANAGERSCRIPT_H
