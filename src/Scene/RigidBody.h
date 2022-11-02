//
// Created by jaaps on 02/11/2022.
//

#ifndef GOLFENGINE_RIGIDBODY_H
#define GOLFENGINE_RIGIDBODY_H


#include "RigidBodyTypes.h"
#include "Component.h"
class RigidBody : public Component {
private:
    float _mass;
    float _gravityScale;
    RigidBodyTypes _bodyType;
};


#endif //GOLFENGINE_RIGIDBODY_H
