//
// Created by marcello on 12/17/22.
//

#include "FinishLevelAreaObject.h"
#include "Scene/Components/BoxCollider.h"
#include "Scene/Components/RigidBody.h"

FinishLevelAreaObject::FinishLevelAreaObject(const Vector2& position, const Vector2& extents) {
    tag = TAG_FINISH;
    addComponent<BoxCollider>(extents);
    addComponent<RigidBody>(RigidBodyDef{RigidBodyTypes::AreaBody});
    setLocalPosition(position);
}
