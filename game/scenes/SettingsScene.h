//
// Created by olafv on 12/14/2022.
//

#ifndef GOLFENGINE_SETTINGSSCENE_H
#define GOLFENGINE_SETTINGSSCENE_H


#include "Scene/ISceneFactory.h"
#include "Scene/GameObjects/UIObject/Button.h"
#include "Scene/GameObjects/UIObject/Text.h"

class SettingsScene : public ISceneFactory {
public:
    void build(Scene& scene) const override;

};


#endif //GOLFENGINE_SETTINGSSCENE_H
