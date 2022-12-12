//
// Created by Lucas on 12-12-2022.
//

#ifndef GOLFENGINE_ENEMYMOVEMENTSCRIPT_H
#define GOLFENGINE_ENEMYMOVEMENTSCRIPT_H


#include "Scene/Components/BehaviourScript.h"
#include "Scene/Components/Pathfinding.h"

class EnemyMovementScript : public BehaviourScript{
public:
    EnemyMovementScript(GameObject* target);
    void onStart() override;

    void onUpdate() override;
private:
    float timePassed = 0;
    std::optional<std::reference_wrapper<Pathfinding>> pathfinding;
    bool chasing;
    GameObject& _target;

    bool checkIftargetIsInSight();
};

#endif //GOLFENGINE_ENEMYMOVEMENTSCRIPT_H
