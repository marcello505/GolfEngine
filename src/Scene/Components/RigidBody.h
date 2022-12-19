//
// Created by jaaps on 02/11/2022.
//

#ifndef GOLFENGINE_RIGIDBODY_H
#define GOLFENGINE_RIGIDBODY_H

#include <optional>
#include <vector>

#include "../Vector2.h"
#include "RigidBodyTypes.h"
#include "Collider.h"
#include "Component.h"
#include "../IPersistable.h"

namespace GolfEngine::Scene::Components {
/// This contains all the initial values of the RigidBody.
/// If you want to adjust any of these properties during runtime,
/// you'll have to make use of the setters and getters from RigidBody
    struct RigidBodyDef {
        RigidBodyTypes bodyType{RigidBodyTypes::DynamicBody};
        float linearDamping{0.0f};
        float angularDamping{0.0f};
        bool fixedRotation{false};
        float gravityScale{1.0f};
        float friction{0.2f};
        float restitution{0.0f};
        float density{1.0f};
        /// Setting this to true give more accurate collision behavior at the cost of more processing power
        bool intensiveCollisions{false};
    };


    class RigidBody : public Component {
    public:
        /// Component that gets registered to the physics engine
        /// \param rigidBodyDef properties of the rigid body
        explicit RigidBody(const RigidBodyDef &rigidBodyDef) : _rigidBodyDef{rigidBodyDef} {}

        RigidBody() : RigidBody(RigidBodyDef{}) {}

        // Overrides
        void onStart() override;
        void onUpdate() override;
        void onRemove() override;
        bool getActive() override;
        void setActive(bool active) override;
        void setParentGameObject(GameObject &gameObject) override;

        // Ipersistable overrides
        std::unique_ptr<ISnapshot> saveSnapshot() override;
        void loadSnapshot(const ISnapshot &rawSnapshot) override;

        //Getters
        [[nodiscard]] const RigidBodyDef &getRigidBodyDef() const;
        [[nodiscard]] std::vector<Collider *> getColliders() const;
        [[nodiscard]] GameObject *getParentGameObject() const;

        //Pass Through methods - Getters
        Vector2 getLinearVelocity();
        float getAngularVelocity();

        //Pass Through methods - Setters
        void applyLocalForceToCenter(const Vector2 &force);
        void applyWorldForceToCenter(const Vector2 &force);
        void setTransform(const Transform &transform);
        void setLinearDamping(float linearDamping);
        void setAngularDamping(float angularDamping);
        void setFixedRotation(bool fixedRotation);
        void setGravityScale(float gravityScale);
        void setLinearVelocity(const Vector2 &velocity);
        void setAngularVelocity(float omega);

    private:
        bool _active{true};
        RigidBodyDef _rigidBodyDef;

        //Snapshot
        struct Snapshot : public ISnapshot {
            Vector2 linearVelocity{};
            float angularVelocity{};
            bool active{};
        };
    };
}

#endif //GOLFENGINE_RIGIDBODY_H
