//
// Created by jaaps on 02/11/2022.
//

#ifndef GOLFENGINE_PATHFINDING_H
#define GOLFENGINE_PATHFINDING_H


#include <vector>
#include "Vector2.h"
#include "Component.h"
class Pathfinding : public Component{
public:
    void navigateToPosition(Vector2 pos);
};


#endif //GOLFENGINE_PATHFINDING_H
