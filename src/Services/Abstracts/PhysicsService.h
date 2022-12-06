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

    //RigidBody specific methods - Getters
    virtual Vector2 getLinearVelocity(RigidBody* pBody) = 0;

    //RigidBody specific methods - Setters
    virtual void applyForceToCenter(RigidBody* pRigidBody, const Vector2& force) = 0;
    virtual void setTransform(RigidBody* pRigidBody, const Transform& transform) = 0;
    virtual void setEnabled(RigidBody* pRigidBody, bool enabled) = 0;
    virtual void setLinearDamping(RigidBody* pRigidBody, float linearDamping) = 0;
    virtual void setAngularDamping(RigidBody* pRigidBody, float angularDamping) = 0;
    virtual void setFixedRotation(RigidBody* pRigidBody, bool fixedRotation) = 0;
    virtual void setGravityScale(RigidBody* pRigidBody, float gravityScale) = 0;
    virtual void setLinearVelocity(RigidBody* pRigidBody, const Vector2& velocity) = 0;

};


#endif //SPC_PROJECT_PHYSICSSERVICE_H
