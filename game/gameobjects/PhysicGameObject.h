//
// Created by Lucas on 16-12-2022.
//

#ifndef GOLFENGINE_PHYSICGAMEOBJECT_H
#define GOLFENGINE_PHYSICGAMEOBJECT_H


#include "Scene/GameObjects/GameObject.h"

using namespace GolfEngine::Scene;

class PhysicGameObject : public GameObject{

public:
    explicit PhysicGameObject(const std::string& imagePath, Vector2 pixelScale, Vector2 extents = Vector2{25.5f, 25.5f});
private:
    std::string _imagePath;
};


#endif //GOLFENGINE_PHYSICGAMEOBJECT_H
