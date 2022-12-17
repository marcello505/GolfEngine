//
// Created by Lucas on 16-12-2022.
//

#ifndef GOLFENGINE_PHYSICGAMEOBJECT_H
#define GOLFENGINE_PHYSICGAMEOBJECT_H


#include "Scene/GameObjects/GameObject.h"

class PhysicGameObject : public GameObject{

public:
    explicit PhysicGameObject(const std::string& imagePath, Vector2 pixelScale);
private:
    std::string _imagePath;
};


#endif //GOLFENGINE_PHYSICGAMEOBJECT_H
