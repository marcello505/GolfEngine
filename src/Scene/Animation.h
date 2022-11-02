//
// Created by jaaps on 02/11/2022.
//

#ifndef GOLFENGINE_ANIMATION_H
#define GOLFENGINE_ANIMATION_H


#include <string>

struct Animation {
private:
    std::string _spriteSheetPath;
    float _playSpeed;
    int _rows;
    int _cols;
    int _beginCell;
    int _endCell;
};


#endif //GOLFENGINE_ANIMATION_H
