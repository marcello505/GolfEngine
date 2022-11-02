//
// Created by conner on 11/2/2022.
//

#ifndef SPC_PROJECT_PHYSICSSERVICE_H
#define SPC_PROJECT_PHYSICSSERVICE_H

// TODO replace with include
//#include "../../Scene/Rigidbody.h"
class Rigidbody;

class PhysicsService {
public:
    virtual void addRigidBody(const Rigidbody& rigidBody) = 0;
    virtual void removeRigidBody(const Rigidbody& rigidBody) = 0;
    virtual void update() = 0;
};


#endif //SPC_PROJECT_PHYSICSSERVICE_H
