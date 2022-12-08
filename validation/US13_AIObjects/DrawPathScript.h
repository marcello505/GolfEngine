//
// Created by conner on 11/24/2022.
//

#ifndef GOLFENGINE_ZOMBIESCRIPT_H
#define GOLFENGINE_ZOMBIESCRIPT_H

#include "Scene/Components/BehaviourScript.h"
#include "Scene/Components/Pathfinding.h"
#include "Core/Time.h"

class DrawPathScript : public BehaviourScript{
public:
    void onStart() override;

    void onUpdate() override;
private:
    float timePassed = 0;
    std::optional<std::reference_wrapper<Pathfinding>> pathfinding;
};

#endif //GOLFENGINE_ZOMBIESCRIPT_H
