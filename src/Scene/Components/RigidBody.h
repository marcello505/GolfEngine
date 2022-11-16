//
// Created by jaaps on 02/11/2022.
//

#ifndef GOLFENGINE_RIGIDBODY_H
#define GOLFENGINE_RIGIDBODY_H


#include "../Vector2.h"
#include <vector>
#include "RigidBodyTypes.h"
#include "Collider.h"
#include "Component.h"

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
    void setParentGameObject(GameObject* gameObject) override;
    Component* clone() const override;

    //Getters
    const RigidBodyDef& getRigidBodyDef() const;
    std::vector<Collider*> getColliders() const;
    GameObject* getParentGameObject() const;

    //Pass Through methods
    void applyForceToCenter(const Vector2& force);
    void setTransform(const Transform& transform);



private:
    GameObject* _parent {};
    RigidBodyDef _rigidBodyDef;
};


#endif //GOLFENGINE_RIGIDBODY_H
