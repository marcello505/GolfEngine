//
// Created by marcello on 11/29/22.
//

#ifndef GOLFENGINE_WALL_H
#define GOLFENGINE_WALL_H

#include "Scene/GameObjects/GameObject.h"

using namespace GolfEngine::Scene;

class Wall : public GolfEngine::Scene::GameObject {
public:
    Wall(const Vector2& position, const Vector2& size);
};


#endif //GOLFENGINE_WALL_H
