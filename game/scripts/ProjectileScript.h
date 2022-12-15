//
// Created by marcello on 12/1/22.
//

#ifndef GOLFENGINE_PROJECTILESCRIPT_H
#define GOLFENGINE_PROJECTILESCRIPT_H

#include <Scene/Components/BehaviourScript.h>
#include "Scene/Components/RigidBody.h"


class ProjectileScript : public BehaviourScript {
public:
    void onStart() override;
    void onUpdate() override;
    void onCollisionEnter(RigidBody& other) override;

    void shoot(const Transform& transform, const Vector2& direction);

    std::unique_ptr<ISnapshot> saveSnapshot() override;

    void loadSnapshot(const ISnapshot& rawSnapshot) override;

private:
    Vector2 _dir {};
    float _bulletSpeed {25.0f};

    int _ticksToLive{};
    RigidBody* _rigidBody {};

    struct Snapshot : public ISnapshot{
        Vector2 dir {};
        int ticksToLive {};
    };

};


#endif //GOLFENGINE_PROJECTILESCRIPT_H
