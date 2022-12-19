//
// Created by Lucas on 12-12-2022.
//

#ifndef GOLFENGINE_ENEMYMOVEMENTSCRIPT_H
#define GOLFENGINE_ENEMYMOVEMENTSCRIPT_H


#include "Scene/Components/BehaviourScript.h"
#include "Scene/Components/Pathfinding.h"

using namespace GolfEngine::Scene;
using namespace GolfEngine::Scene::Components;

class EnemyMovementScript : public BehaviourScript{
public:
    explicit EnemyMovementScript(GameObject* target);
    void onStart() override;

    void onUpdate() override;
    void rotateEnemyToPosition(Vector2 targetPosition);

    std::unique_ptr<ISnapshot> saveSnapshot() override;
    void loadSnapshot(const ISnapshot& rawSnapshot) override;

private:
    std::optional<std::reference_wrapper<Pathfinding>> pathfinding;
    bool chasing {false};
    GameObject& _target;
    int patrolIndex{0};
    Vector2 direction {0,0};

    bool checkIftargetIsInSight();

    struct Snapshot : public ISnapshot{
        bool chasing {};
        int patrolIndex {};
        Vector2 direction {0,0};
    };

};

#endif //GOLFENGINE_ENEMYMOVEMENTSCRIPT_H
