//
// Created by Lucas on 16-12-2022.
//

#ifndef GOLFENGINE_ENEMYCOLLISIONSCRIPT_H
#define GOLFENGINE_ENEMYCOLLISIONSCRIPT_H

#include "Scene/Components/BehaviourScript.h"
#include "EnemyMovementScript.h"

class EnemyCollisionScript : public BehaviourScript {
    void onStart() override;
    void onUpdate() override;
    void onCollisionEnter(RigidBody& other) override;
private:
    EnemyMovementScript* _enemyMovement;
    bool _death{false};
};

#endif //GOLFENGINE_ENEMYCOLLISIONSCRIPT_H
