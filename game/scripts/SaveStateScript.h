//
// Created by marcello on 12/6/22.
//

#ifndef GOLFENGINE_SAVESTATESCRIPT_H
#define GOLFENGINE_SAVESTATESCRIPT_H

#include <Scene/Components/BehaviourScript.h>
#include "Input/ActionMap.h"

using namespace GolfEngine::Input;
using namespace GolfEngine::Scene::Components;

class SaveStateScript : public BehaviourScript{
public:
    void onStart() override;
    void onUpdate() override;

private:
    ActionMap* _actionMap {};
};


#endif //GOLFENGINE_SAVESTATESCRIPT_H
