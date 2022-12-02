//
// Created by marcello on 12/1/22.
//

#include <Core/SceneManager.h>

#include "ProjectilePoolScript.h"

std::optional<std::reference_wrapper<ProjectileScript>> ProjectilePoolScript::getProjectile() {
    auto& children = _gameObject.value().get().children();

    for(auto item = children.begin(); item != children.end(); ++item){
        if(!item->get().getActive() && item->get().hasComponent<ProjectileScript>()){
            return item->get().getComponent<ProjectileScript>();
        }
    }
    return {};
}
