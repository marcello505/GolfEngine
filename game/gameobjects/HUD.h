//
// Created by conner on 12/15/2022.
//

#ifndef GOLFENGINE_HUD_H
#define GOLFENGINE_HUD_H

#include <Scene/GameObjects/GameObject.h>
#include <Scene/Scene.h>

using namespace GolfEngine::Scene;

class HUD : public GameObject {
public:
    explicit HUD(Scene& scene);
};


#endif //GOLFENGINE_HUD_H
