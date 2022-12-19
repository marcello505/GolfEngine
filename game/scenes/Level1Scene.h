//
// Created by Lucas on 15-12-2022.
//

#ifndef GOLFENGINE_LEVEL1SCENE_H
#define GOLFENGINE_LEVEL1SCENE_H


#include "Scene/ISceneFactory.h"

using namespace GolfEngine::Scene;

class Level1Scene : public ISceneFactory{
public:
    void build(Scene& scene) const override;

};


#endif //GOLFENGINE_LEVEL1SCENE_H
