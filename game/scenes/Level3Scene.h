//
// Created by olafv on 12/17/2022.
//

#ifndef GOLFENGINE_LEVEL3SCENE_H
#define GOLFENGINE_LEVEL3SCENE_H


#include "Scene/ISceneFactory.h"

class Level3Scene : public ISceneFactory{
public:
    void build(Scene& scene) const override;

};



#endif //GOLFENGINE_LEVEL3SCENE_H
