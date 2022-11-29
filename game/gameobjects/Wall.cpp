//
// Created by marcello on 11/29/22.
//

#include <Scene/Components/BoxCollider.h>
#include <Scene/Components/RigidBody.h>

#include "Wall.h"

Wall::Wall(const Vector2& position, const Vector2& size) {
    addComponent<BoxCollider>(size);
    addComponent<RigidBody>(RigidBodyDef{RigidBodyTypes::StaticBody});
    setLocalPosition(position);
}
