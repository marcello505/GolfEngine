//
// Created by marcello on 12/1/22.
//

#include "Projectile.h"
#include "Scene/Components/RigidBody.h"
#include "Scene/Components/BoxCollider.h"
#include "../scripts/ProjectileScript.h"

Projectile::Projectile() {
    addComponent<BoxCollider>(Vector2{7.5f, 7.5f});
    addComponent<RigidBody>();
    addComponent<ProjectileScript>();
}
