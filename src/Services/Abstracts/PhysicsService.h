//
// Created by conner on 11/2/2022.
//

#ifndef SPC_PROJECT_PHYSICSSERVICE_H
#define SPC_PROJECT_PHYSICSSERVICE_H
#include "../../Scene/Components/RigidBody.h"
#include "../../Scene/Vector2.h"
#include "../../Core/Time.h"


class PhysicsService {
public:
    virtual void addRigidBody(RigidBody* pRigidBody) = 0;
    virtual void removeRigidBody(RigidBody* pRigidBody) = 0;
    virtual void update(GameTic timeStep) = 0;
    virtual void setGravity(const Vector2& vec2) = 0;
};


#endif //SPC_PROJECT_PHYSICSSERVICE_H
