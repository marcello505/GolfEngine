//
// Created by Lucas on 16-12-2022.
//

#ifndef GOLFENGINE_ENEMYCOLLISIONSCRIPT_H
#define GOLFENGINE_ENEMYCOLLISIONSCRIPT_H

#include "Scene/Components/BehaviourScript.h"
#include <Scene/Components/ParticleSystem.h>
#include <Scene/Components/AudioSource.h>
#include "EnemyMovementScript.h"

using namespace GolfEngine::Scene::Components;

class EnemyCollisionScript : public BehaviourScript {
public:
    void onStart() override;
    void onUpdate() override;
    void onCollisionEnter(RigidBody& other) override;
    bool isDead() const;


    std::unique_ptr<ISnapshot> saveSnapshot() override;
    void loadSnapshot(const ISnapshot& rawSnapshot) override;
private:
    EnemyMovementScript* _enemyMovement;
    bool _death{false};

    struct Snapshot : public ISnapshot{
        bool death;
    };
    ParticleSystem* _particleSystem;
    AudioSource* _audioSource;
};

#endif //GOLFENGINE_ENEMYCOLLISIONSCRIPT_H
