//
// Created by conner on 11/2/2022.
//

#ifndef SPC_PROJECT_BOX2DPHYSICSSERVICE_H
#define SPC_PROJECT_BOX2DPHYSICSSERVICE_H

#include <box2d/box2d.h>
#include <map>
#include <optional>
#include "Abstracts/PhysicsService.h"

/// Box2D has it's own units than the ones used the game world, thus a conversion needs to happen inbetween the
/// physics layer and the scene layer. This float is the factor used for this conversion.
#define PhysicsSpaceToWorldSpace 100.0f
#define DefaultVelocityIterations 8
#define DefaultPositionIterations 3

namespace GolfEngine::Services::Physics{
    class RaysCastCallback : public b2RayCastCallback
    {
    public:
        RaysCastCallback() : m_fixture{nullptr} {
        }
        float ReportFixture(b2Fixture *fixture, const b2Vec2 &point, const b2Vec2 &normal, float fraction) override;
        b2Fixture* m_fixture;
        b2Vec2 m_point;
        b2Vec2 m_normal;
        float m_fraction;
    };

    class Box2DPhysicsService :  public PhysicsService {
    public:
        // Constructors
        Box2DPhysicsService(int velIterations, int posIterations);
        explicit Box2DPhysicsService() : Box2DPhysicsService(DefaultVelocityIterations, DefaultPositionIterations) {}

        // Methods
        /// Adds the given RigidBody to the physics world. On a nullptr nothing happens
        /// \param pRigidBody
        void addRigidBody(RigidBody* pRigidBody) override;
        /// Removes the given RigidBody from the physics world, if no RigidBody was found nothing happens.
        /// \param pRigidBody The RigidBody to remove.
        void removeRigidBody(RigidBody* pRigidBody) override;
        void update(GameTic timeStep) override;
        void setGravity(const Vector2& vec2) override;

        // RigidBody specific methods - Getters
        Vector2 getLinearVelocity(RigidBody* pBody) override;
        float getAngularVelocity(RigidBody* pBody) override;
        bool raycastWorld(RigidBody* start, RigidBody* target) override;

        // RigidBody specific methods - Setters
        void applyLocalForceToCenter(RigidBody* pRigidBody, const Vector2& force) override;
        void applyWorldForceToCenter(RigidBody* pRigidBody, const Vector2& force) override;
        void setTransform(RigidBody* pRigidBody, const Transform& transform) override;
        void setEnabled(RigidBody* pRigidBody, bool enabled) override;
        void setLinearDamping(RigidBody* pRigidBody, float linearDamping) override;
        void setAngularDamping(RigidBody* pRigidBody, float angularDamping) override;
        void setFixedRotation(RigidBody* pRigidBody, bool fixedRotation) override;
        void setGravityScale(RigidBody* pRigidBody, float gravityScale) override;
        void setLinearVelocity(RigidBody* pRigidBody, const Vector2& velocity) override;
        void setAngularVelocity(RigidBody* pRigidBody, float omega) override;

        std::vector<Collider*> getStaticColliders() override;

        // Methods for testing
        int getBodyCount() const;
        int getFixtureCount() const;

        std::optional<std::reference_wrapper<RigidBody>> getRigidBodyWithB2Body(b2Body& body);
    private:
        // Fields
        /// Start the box2d world with (0.0, 0.0) gravity
        b2World _world {{0.f, 0.f}};
        /// Used in the b2World.Step() function, see Box2D documentation for more info
        const int _velocityIterations;
        /// Used in the b2World.Step() function, see Box2D documentation for more info
        const int _positionIterations;

        // Methods
        std::map<RigidBody*, b2Body*> _rigidBodies {};
        std::optional<b2Body*> getB2Body(RigidBody* rigidBody) const;
    };

}



#endif //SPC_PROJECT_BOX2DPHYSICSSERVICE_H
