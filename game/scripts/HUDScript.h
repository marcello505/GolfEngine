//
// Created by conner on 12/15/2022.
//

#ifndef GOLFENGINE_HUDSCRIPT_H
#define GOLFENGINE_HUDSCRIPT_H

#include <Scene/Components/BehaviourScript.h>
#include <Scene/GameObjects/UIObject/Text.h>

class HUDScript : public BehaviourScript {
    struct Snapshot : public ISnapshot{
        float timePassed {0.0f};
    };
public:
    HUDScript(Text* fpsText, Text* timeText);
    void onUpdate() override;

    std::unique_ptr<ISnapshot> saveSnapshot() override;
    void loadSnapshot(const ISnapshot& rawSnapshot) override;
private:
    Text* _fpsText, *_timeText;
    bool _renderFPS;
    float _timePassed;
};


#endif //GOLFENGINE_HUDSCRIPT_H
