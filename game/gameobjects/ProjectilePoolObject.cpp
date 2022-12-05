//
// Created by marcello on 12/2/22.
//

#include "ProjectilePoolObject.h"
#include "Projectile.h"
#include "../scripts/ProjectilePoolScript.h"

ProjectilePoolObject::ProjectilePoolObject(Scene& scene, int capacity) {
    addComponent<ProjectilePoolScript>();

    GameObject& parent = *this;
    for(int i = 0; i < capacity; ++i){
        scene.createNewGameObject<Projectile>(parent);
    }
}
