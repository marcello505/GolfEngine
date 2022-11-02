//
// Created by jaaps on 02/11/2022.
//

#ifndef GOLFENGINE_RIGIDBODY_H
#define GOLFENGINE_RIGIDBODY_H


#include "RigidBodyTypes.h"

struct RigidBody {
private:
    float _mass;
    float _gravityScale;
    RigidBodyTypes _bodyType;
};


#endif //GOLFENGINE_RIGIDBODY_H
