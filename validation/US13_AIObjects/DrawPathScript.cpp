//
// Created by conner on 11/24/2022.
//

#include "DrawPathScript.h"
#include "Services/Singletons/PathfindingSingleton.h"
#include "Scene/Components/RigidBody.h"

void DrawPathScript::onStart() {
    pathfinding = _gameObject->get().getComponent<Pathfinding>();
}

void DrawPathScript::onUpdate() {
    auto direction = pathfinding->get().getPathDirection();
    auto rb = &_gameObject.value().get().getComponent<RigidBody>();
    rb->applyWorldForceToCenter(direction * 0.05);
}
