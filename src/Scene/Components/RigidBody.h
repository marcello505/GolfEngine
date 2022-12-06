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

/// This contains all the initial values of the RigidBody.
/// If you want to adjust any of these properties during runtime,
/// you'll have to make use of the setters and getters from RigidBody
struct RigidBodyDef{
    RigidBodyTypes bodyType {RigidBodyTypes::DynamicBody};
    float linearDamping {0.0f};
    float angularDamping {0.0f};
    bool fixedRotation {false};
    float gravityScale {1.0f};
    float friction {0.2f};
    float restitution {0.0f};
    float density {1.0f};
};


class RigidBody : public Component {
public:
    explicit RigidBody(const RigidBodyDef& rigidBodyDef) : _rigidBodyDef{rigidBodyDef} {}
    RigidBody() : RigidBody(RigidBodyDef{}) {}

    // Overrides
    void onStart() override;
    void onUpdate() override;
    void onRemove() override;
    bool getActive() override;
    void setActive(bool active) override;
    void setParentGameObject(GameObject& gameObject) override;
    std::unique_ptr<ISnapshot> saveSnapshot() override;
    void loadSnapshot(const ISnapshot& rawSnapshot) override;


    //Getters
    const RigidBodyDef& getRigidBodyDef() const;
    std::vector<Collider*> getColliders() const;
    GameObject* getParentGameObject() const;

    //Pass Through methods - Getters
    Vector2 getLinearVelocity();

    //Pass Through methods - Setters
    void applyForceToCenter(const Vector2& force);
    void setTransform(const Transform& transform);
    void setLinearDamping(float linearDamping);
    void setAngularDamping(float angularDamping);
    void setFixedRotation(bool fixedRotation);
    void setGravityScale(float gravityScale);
    void setLinearVelocity(const Vector2& velocity);

private:
    bool _active {true};
    RigidBodyDef _rigidBodyDef;

    //Snapshot
    struct Snapshot : public ISnapshot{
        Vector2 linearVelocity {};
        bool active {};
    };
};


#endif //GOLFENGINE_RIGIDBODY_H
