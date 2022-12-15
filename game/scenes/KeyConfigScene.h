//
// Created by olafv on 12/15/2022.
//

#ifndef GOLFENGINE_KEYCONFIGSCENE_H
#define GOLFENGINE_KEYCONFIGSCENE_H

#include "Scene/ISceneFactory.h"
#include "Scene/GameObjects/UIObject/Button.h"
#include "Scene/GameObjects/UIObject/Text.h"

class KeyConfigScene : public ISceneFactory {
public:
    void build(Scene& scene) const override;

};


#endif //GOLFENGINE_KEYCONFIGSCENE_H
