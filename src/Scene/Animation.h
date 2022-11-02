//
// Created by jaaps on 02/11/2022.
//

#ifndef GOLFENGINE_ANIMATION_H
#define GOLFENGINE_ANIMATION_H


#include <string>

struct Animation {

    std::string _priteSheetPath;
    float playSpeed;
    int rows;
    int cols;
    int beginCell;
    int endCell;
};


#endif //GOLFENGINE_ANIMATION_H
