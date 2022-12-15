//
// Created by marcello on 12/1/22.
//

#include "Projectile.h"
#include "Scene/Components/RigidBody.h"
#include "../scripts/ProjectileScript.h"
#include "Scene/Components/CircleCollider.h"

Projectile::Projectile() {
    addComponent<CircleCollider>(5.0f);

    RigidBodyDef def {};
    def.intensiveCollisions = true;
    addComponent<RigidBody>(def);
    addComponent<ProjectileScript>();
}
