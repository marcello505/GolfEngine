//
// Created by conner on 11/23/2022.
//

#ifndef GOLFENGINE_UISCENE_H
#define GOLFENGINE_SCENEFACTORY_H

#include "Scene/ISceneFactory.h"

class UIScene : public ISceneFactory{
    void build(Scene& scene) const override;
};


#endif //GOLFENGINE_UISCENE_H
