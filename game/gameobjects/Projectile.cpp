//
// Created by marcello on 12/1/22.
//

#include "Projectile.h"
#include "Scene/Components/RigidBody.h"
#include "../scripts/ProjectileScript.h"
#include "Scene/Components/CircleCollider.h"
#include "Scene/Components/SpriteComponent.h"

Projectile::Projectile() {
    tag = "projectile";
    addComponent<CircleCollider>(7.0f);
    RigidBodyDef def {};
    def.intensiveCollisions = true;
    addComponent<RigidBody>(def);
    addComponent<SpriteComponent>(R"(res/sprites/bullet.png)", Vector2{1.75f,1.75f});
    addComponent<ProjectileScript>();
}
