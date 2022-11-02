//
// Created by jaaps on 02/11/2022.
//

#ifndef GOLFENGINE_RIGIDBODY_H
#define GOLFENGINE_RIGIDBODY_H


#include "RigidBodyTypes.h"

struct RigidBody {
public:
    float mass;
    float gravityScale;
    RigidBodyTypes bodyType;
};


#endif //GOLFENGINE_RIGIDBODY_H
