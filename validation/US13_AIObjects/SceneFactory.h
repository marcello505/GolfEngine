//
// Created by conner on 11/23/2022.
//

#ifndef GOLFENGINE_SCENEFACTORY_H
#define GOLFENGINE_SCENEFACTORY_H

#include "Scene/ISceneFactory.h"
#include "Scene/Components/Collider.h"

class SceneFactory : public ISceneFactory{
    void build(Scene& scene) const override;
    bool isValidSpot(Vector2 pos, std::vector<Collider*> colliders) const;
};


#endif //GOLFENGINE_SCENEFACTORY_H
