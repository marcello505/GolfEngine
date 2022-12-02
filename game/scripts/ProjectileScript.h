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

    void shoot(const Transform& transform, const Vector2& direction);

private:
    Vector2 _dir {};

    int _ticksToLive{};
    float _ttl {};
    RigidBody* _rigidBody {};


};


#endif //GOLFENGINE_PROJECTILESCRIPT_H
