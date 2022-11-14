//
// Created by conner on 11/2/2022.
//

#ifndef SPC_PROJECT_BOX2DPHYSICSSERVICE_H
#define SPC_PROJECT_BOX2DPHYSICSSERVICE_H

#include <box2d/box2d.h>
#include <map>
#include <optional>
#include "Abstracts/PhysicsService.h"

namespace GolfEngine::Services::Physics{
    class Box2DPhysicsService :  public PhysicsService {
    public:
        Box2DPhysicsService();
        void addRigidBody(RigidBody* pRigidBody) override;

        /// Removes the given RigidBody from the physics world, if no RigidBody was found nothing happens.
        /// \param pRigidBody The RigidBody to remove.
        void removeRigidBody(RigidBody* pRigidBody) override;
        void update() override;
        void setGravity(const Vector2& vec2) override;

        // Methods for testing
        int getBodyCount() const;
    private:
        /// Box2D has it's own units than the ones used the game world, thus a conversion needs to happen inbetween the
        /// physics layer and the scene layer. This float is the factor used for this conversion.
        constexpr const static float _physicsSpace2WorldSpace {100.0f};

        /// Start the box2d world with (0.0, 0.0) gravity
        b2World _world {{0.f, 0.f}};
        std::map<RigidBody*, b2Body*> _rigidBodies {};

        std::optional<b2Body*> getB2Body(RigidBody* rigidBody) const;
    };

}



#endif //SPC_PROJECT_BOX2DPHYSICSSERVICE_H
