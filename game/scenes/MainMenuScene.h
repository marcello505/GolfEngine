//
// Created by olafv on 12/13/2022.
//

#ifndef GOLFENGINE_MAINMENUSCENE_H
#define GOLFENGINE_MAINMENUSCENE_H

#include "Scene/ISceneFactory.h"
#include "Scene/GameObjects/UIObject/Button.h"
#include "Scene/GameObjects/UIObject/Text.h"

class MainMenuScene : public ISceneFactory {
public:
    void build(Scene& scene) const override;

};



#endif //GOLFENGINE_MAINMENUSCENE_H
