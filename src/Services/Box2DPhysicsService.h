//
// Created by conner on 11/2/2022.
//

#ifndef SPC_PROJECT_BOX2DPHYSICSSERVICE_H
#define SPC_PROJECT_BOX2DPHYSICSSERVICE_H

#include "Abstracts/PhysicsService.h"
#include <vector>

class Box2DPhysicsService :  public PhysicsService {
public:
    Box2DPhysicsService();
    void addRigidBody(const RigidBody& rigidBody) override;
    void removeRigidBody(const RigidBody& rigidBody) override;
    void update() override;
private:
    std::vector<RigidBody*> _rigidBodies;
};


#endif //SPC_PROJECT_BOX2DPHYSICSSERVICE_H