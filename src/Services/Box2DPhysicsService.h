//
// Created by conner on 11/2/2022.
//

#ifndef SPC_PROJECT_BOX2DPHYSICSSERVICE_H
#define SPC_PROJECT_BOX2DPHYSICSSERVICE_H

#include "Abstracts/PhysicsService.h"
#include "../Scene/Rigidbody.h"
#include <vector>

class Box2DPhysicsService :  public PhysicsService {
public:
    Box2DPhysicsService();
    void addRigidBody(RigidBody& rigidBody) override;
    void removeRigidBody(RigidBody& rigidBody) override;
    void update() override;
private:
    std::vector<Rigidbody> _rigidBodies;
};


#endif //SPC_PROJECT_BOX2DPHYSICSSERVICE_H
