//
// Created by marcello on 12/1/22.
//

#ifndef GOLFENGINE_PROJECTILEPOOLSCRIPT_H
#define GOLFENGINE_PROJECTILEPOOLSCRIPT_H

#include <optional>

#include <Scene/Components/BehaviourScript.h>

#include "ProjectileScript.h"

using namespace GolfEngine::Scene::Components;

class ProjectilePoolScript : public BehaviourScript{
public:
    /// Gets an projectile that is currently unactive
    std::optional<std::reference_wrapper<ProjectileScript>> getProjectile();
};


#endif //GOLFENGINE_PROJECTILEPOOLSCRIPT_H
