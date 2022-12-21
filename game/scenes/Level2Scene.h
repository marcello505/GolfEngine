//
// Created by marcello on 12/15/22.
//

#ifndef GOLFENGINE_LEVEL2SCENE_H
#define GOLFENGINE_LEVEL2SCENE_H

#include "Scene/ISceneFactory.h"

using namespace GolfEngine::Scene;

class Level2Scene : public ISceneFactory{
public:
    void build(Scene& scene) const override;

};


#endif //GOLFENGINE_LEVEL2SCENE_H
