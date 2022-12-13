//
// Created by marcello on 12/6/22.
//

#ifndef GOLFENGINE_TESTBLOCK_H
#define GOLFENGINE_TESTBLOCK_H

#include <Scene/GameObjects/GameObject.h>

class TestBlock : public GameObject {
public:
    explicit TestBlock(const Vector2& position, const Vector2& size = {15.0f, 15.0f});

};


#endif //GOLFENGINE_TESTBLOCK_H
