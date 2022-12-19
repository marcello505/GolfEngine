//
// Created by olafv on 12/18/2022.
//

#ifndef GOLFENGINE_YOUWONSCENE_H
#define GOLFENGINE_YOUWONSCENE_H

#include "Scene/ISceneFactory.h"
#include "Scene/GameObjects/UIObject/Button.h"
#include "Scene/GameObjects/UIObject/Text.h"

class YouWonScene : public ISceneFactory {
public:
    void build(Scene& scene) const override;

};


#endif //GOLFENGINE_YOUWONSCENE_H
