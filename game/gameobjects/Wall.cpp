//
// Created by marcello on 11/29/22.
//

#include <Scene/Components/BoxCollider.h>
#include <Scene/Components/RigidBody.h>

#include "Wall.h"

using namespace GolfEngine::Scene::Components;

Wall::Wall(const Vector2& position, const Vector2& size) {
    addComponent<BoxCollider>(size);
    addComponent<RigidBody>(RigidBodyDef{RigidBodyTypes::StaticBody});
    setLocalPosition(position);
}
