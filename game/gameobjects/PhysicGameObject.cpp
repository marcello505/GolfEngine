//
// Created by Lucas on 16-12-2022.
//

#include "PhysicGameObject.h"
#include "Scene/Components/BoxCollider.h"
#include "Scene/Components/RigidBody.h"
#include "Scene/Components/SpriteComponent.h"

PhysicGameObject::PhysicGameObject(const std::string &imagePath, Vector2 pixelScale, Vector2 extents){
    addComponent<BoxCollider>(extents);

    RigidBodyDef rbDef {};

    rbDef.linearDamping = 5.0f;
    rbDef.angularDamping = 3.0f;


    addComponent<SpriteComponent>(imagePath, pixelScale);


    addComponent<RigidBody>(rbDef);

}
