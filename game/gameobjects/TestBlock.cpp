//
// Created by marcello on 12/6/22.
//

#include "TestBlock.h"
#include "Scene/Components/BoxCollider.h"
#include "Scene/Components/RigidBody.h"

TestBlock::TestBlock(const Vector2& position, const Vector2& size) {
    addComponent<BoxCollider>(size);

    RigidBodyDef rbDef {};
    rbDef.linearDamping = 1.0f;
    rbDef.angularDamping = 1.0f;

    addComponent<RigidBody>(rbDef);
    setLocalPosition(position);
}
