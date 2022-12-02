//
// Created by marcello on 12/2/22.
//

#ifndef GOLFENGINE_PROJECTILEPOOLOBJECT_H
#define GOLFENGINE_PROJECTILEPOOLOBJECT_H

#include <Scene/Scene.h>
#include <Scene/GameObjects/GameObject.h>

class ProjectilePoolObject : public GameObject {
public:
    explicit ProjectilePoolObject(Scene* scene, int capacity);
};


#endif //GOLFENGINE_PROJECTILEPOOLOBJECT_H
