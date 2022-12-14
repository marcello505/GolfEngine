//
// Created by conner on 11/23/2022.
//

#ifndef GOLFENGINE_UISCENE_H
#define GOLFENGINE_UISCENE_H

#include "Scene/ISceneFactory.h"
#include <Scene/GameObjects/UIObject/Text.h>
#include <Scene/GameObjects/UIObject/Button.h>
#include <Scene/GameObjects/UIObject/Alignment.h>

class UIScene : public ISceneFactory{
    void build(Scene& scene) const override;
};


#endif //GOLFENGINE_UISCENE_H
