//
// Created by conner on 11/2/2022.
//

#ifndef SPC_PROJECT_PHYSICSSERVICE_H
#define SPC_PROJECT_PHYSICSSERVICE_H
#include "../../Scene/Components/RigidBody.h"


class PhysicsService {
public:
    virtual void addRigidBody(const RigidBody& rigidBody) = 0;
    virtual void removeRigidBody(const RigidBody& rigidBody) = 0;
    virtual void update() = 0;
};


#endif //SPC_PROJECT_PHYSICSSERVICE_H
